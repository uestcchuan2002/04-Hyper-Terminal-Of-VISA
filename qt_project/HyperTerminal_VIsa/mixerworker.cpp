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
        const QString name = info.portName();
        const QString path = info.systemLocation();

        if (name.startsWith("ttyUSB") ||
            name.startsWith("ttyACM")) {
            ports << path;
        }
    }

    emit portsUpdated(ports);
}

// ===== 连接串口 =====
void MixerWorker::connectPort(QString portName)
{
    if (serial->isOpen())
        serial->close();

    serial->setPortName(portName);
    /*波特率必须大与等于128000*/
    if (!serial->setBaudRate(128000)) {
        emit miError("[Mixer] set baudrate failed: " + serial->errorString());
    }

    if (serial->open(QIODevice::ReadWrite)) {
        emit miLog("[Mixer] connected: " + portName);
        /*延时100ms，发送01 00 06 00 00 00 进入spi模式*/
        QTimer::singleShot(100, this, [=]() {

            QByteArray modeCmd = QByteArray::fromHex("010006000000");
            //测试
            // QByteArray modeCmd = QByteArray::fromHex("010006000003");
            //...
            serial->write(modeCmd);
            serial->flush();
            emit miLog("[Mixer] TX mode: 01 00 06 00 00 00");
        });
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

    QString hexStr = QString(data.toHex(' ')).toUpper();

    emit miLog("[Mixer] RX: " + hexStr);
}

void MixerWorker::onSetComd(int cmd, QString num)
{
    if (!serial->isOpen()) {
        emit miError("[Mixer] Serial not open");
        return;
    }

    bool ok = false;
    quint16 value = num.toUShort(&ok, 10);

    if (!ok) {
        emit miError("[Mixer] invalid value: " + num);
        return;
    }

    if (cmd < 0 || cmd > 2) {
        emit miError("[Mixer] invalid cmd");
        return;
    }

    QByteArray frame = QByteArray::fromHex("070011000001000A000000030000");

    frame.append(static_cast<char>(cmd & 0xFF));
    frame.append(static_cast<char>((value >> 8) & 0xFF));
    frame.append(static_cast<char>(value & 0xFF));
    // 测试
    // QByteArray frame = QByteArray::fromHex("070012000001003200FF0004000290000000");
    serial->write(frame);
    serial->flush();

    emit miLog(QString("[Mixer] TX raw: %1")
                   .arg(QString(frame.toHex(' ')).toUpper()));
}
