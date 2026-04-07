#ifndef MIXERWORKER_H
#define MIXERWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

class MixerWorker : public QObject
{
    Q_OBJECT

public:
    explicit MixerWorker(QObject *parent = nullptr);
    ~MixerWorker();

signals:
    void miLog(QString msg);
    void miError(QString msg);
    void logMessage(QString msg);
    void portsUpdated(QStringList ports);
    void connected(bool ok);

public slots:
    void scanPorts();                       // 扫描串口
    void connectPort(QString portName);     // 连接串口
    void disconnectPort();                  // 断开
    void sendCommand(QString cmd);          // 发送命令
    void onReadyRead();
    void onSetComd(int cmd, QString num);
private:
    QSerialPort *serial;
};

#endif
