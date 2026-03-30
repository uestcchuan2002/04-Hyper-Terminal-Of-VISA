#include "rfworker.h"

RFWorker::RFWorker(QObject *parent) : QObject(parent)
{
}

bool RFWorker::send(const QString &cmd)
{
    QByteArray data = cmd.toLocal8Bit();
    if (!data.endsWith('\n')) data.append('\n');

    ViUInt32 count = 0;
    return (viWrite(dev, (ViBuf)data.data(), data.size(), &count) >= VI_SUCCESS);
}

void RFWorker::connectDevice(QString addr)
{
    if (connected) {
        viClose(dev);
        viClose(rm);
        connected = false;
        emit rfLog("RF disconnected");
        return;
    }

    if (viOpenDefaultRM(&rm) < VI_SUCCESS) {
        emit rfError("RF RM open failed");
        return;
    }

    QByteArray a = addr.toLocal8Bit();

    if (viOpen(rm, a.data(), VI_NULL, VI_NULL, &dev) < VI_SUCCESS) {
        emit rfError("RF open failed");
        return;
    }

    connected = true;
    emit rfLog("RF connected");
    emit connectSuccess(connected);
}


void RFWorker::config(double freq, double power)
{
    if (!connected) return;

    send(QString(":FREQ %1").arg(freq));
    send(QString(":LEV %1").arg(power));
    send(":OUTP ON");

    emit rfLog("RF configured");
}

void RFWorker::writeCmd(QString cmd)
{
    if (!connected) return;

    send(cmd);
    emit rfLog("RF >> " + cmd);
}

void RFWorker::readCmd()
{
    if (!connected) return;

    char buf[1024] = {0};
    ViUInt32 cnt = 0;

    if (viRead(dev, (ViBuf)buf, sizeof(buf), &cnt) >= VI_SUCCESS) {
        emit rfLog("RF << " + QString(buf));
    }
}

void RFWorker::output(bool on)
{
    if (!connected) {
        emit rfError("RF not connected");
        return;
    }

    QString cmd = on ? ":OUTP ON" : ":OUTP OFF";

    if (!send(cmd)) {
        emit rfError("RF output failed");
        return;
    }

    emit rfLog(on ? "RF Output ON" : "RF Output OFF");
}

void RFWorker::disconnectDevice()
{
    if (rm != VI_NULL) {
        viClose(rm);
        rm = VI_NULL;
    }

    if (dev != VI_NULL) {
        viClose(dev);
        dev = VI_NULL;
    }

    connected = false;

    emit rfLog("SIG disconnected");
    emit connectSuccess(connected);
}
