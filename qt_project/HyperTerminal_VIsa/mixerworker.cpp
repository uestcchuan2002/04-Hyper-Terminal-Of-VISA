#include "mixerworker.h"

MixerWorker::MixerWorker(QObject *parent)
    : QObject(parent)
{
    serial = new QSerialPort(this);

    // 串口接收信号
    connect(serial, &QSerialPort::readyRead,
                this, &MixerWorker::onReadyRead);
}

MixerWorker::~MixerWorker()
{
    if (serial->isOpen())
        serial->close();
}

// ===== 扫描串口 =====
void MixerWorker::scanPorts()
{

    QStringList ports;

    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {

        QString name = info.portName();   // 例如 "ttyUSB0"

        // ⭐ 只保留 ttyUSB
        if (!name.startsWith("ttyUSB"))
            continue;

        ports << "/dev/" + name;
    }

    emit portsUpdated(ports);
}

// ===== 连接串口 =====
void MixerWorker::connectPort(QString portName)
{
    if (serial->isOpen())
        serial->close();

    serial->setPortName(portName);
    serial->setBaudRate(QSerialPort::Baud115200);

    if (serial->open(QIODevice::ReadWrite)) {
        emit miLog("[Mixer] connected: " + portName);
        emit connected(true);
    } else {
        emit miError("[Mixer] connect failed!");
        emit connected(false);
    }
}

// ===== 断开 =====
void MixerWorker::disconnectPort()
{
    if (serial->isOpen()) {
        serial->close();
        emit miLog("[Mixer] disconnected");
        emit connected(false);
    }
}

// ===== 发送命令 =====
void MixerWorker::sendCommand(QString cmd)
{
    if (!serial->isOpen()) {
        emit miError("[Mixer] Serial not open");
        return;
    }

    QByteArray data = cmd.toUtf8() + "\r\n";
    serial->write(data);

    emit miLog("[Mixer] TX: " + cmd);
}

void MixerWorker::onReadyRead()
{
    QByteArray data = serial->readAll();

    if (data.isEmpty())
        return;

    QString str = QString::fromUtf8(data);

    emit miLog("[Mixer] RX: " + str);
}

void MixerWorker::onSetComd(int cmd, QString num)
{
    QString temp;
    switch (cmd) {
    case 0:
        temp = "CMD_1 " + num;
        break;
    case 1:
        temp = "CMD_2 " + num.mid(0,2) + " " + num.mid(2, 2);
        break;
    case 2:
        temp = "CMD_2 " + num.mid(0,2) + " " + num.mid(2, 2);
        break;
    }
    sendCommand(temp);
}


