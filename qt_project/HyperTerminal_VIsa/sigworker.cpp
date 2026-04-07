#include "sigworker.h"

SigWorker::SigWorker(QObject *parent) : QObject(parent)
{
}

bool SigWorker::send(const QString &cmd)
{
    QByteArray data = cmd.toLocal8Bit();
    if (!data.endsWith('\n')) data.append('\n');

    ViUInt32 count = 0;
    return (viWrite(dev, (ViBuf)data.data(), data.size(), &count) >= VI_SUCCESS);
}

void SigWorker::connectDevice(QString addr)
{
    if (connected) {
        viClose(dev);
        viClose(rm);
        connected = false;
        emit sigLog("[SIG] disconnected");
        return;
    }

    if (viOpenDefaultRM(&rm) < VI_SUCCESS) {
        emit sigError("[SIG] RM open failed");
        return;
    }

    QByteArray a = addr.toLocal8Bit();

    if (viOpen(rm, a.data(), VI_NULL, VI_NULL, &dev) < VI_SUCCESS) {
        emit sigError("[SIG] open failed");
        return;
    }

    connected = true;
    emit sigLog("[SIG] connected");
    emit connectSuccess(connected);
}

void SigWorker::writeCmd(QString cmd)
{
    if (!connected) return;

    send(cmd);
    emit sigLog("[SIG] >> " + cmd);
}

void SigWorker::readCmd()
{
    if (!connected) return;

    char buf[1024] = {0};
    ViUInt32 cnt = 0;

    if (viRead(dev, (ViBuf)buf, sizeof(buf), &cnt) >= VI_SUCCESS) {
        emit sigLog("[SIG] << " + QString(buf));
    }
}

void SigWorker::downloadWave(QVector<int> points,
                             int channel,
                             double freq,
                             double vpp,
                             double offset)
{
    if (!connected) {
        emit sigError("[SIG] not connected");
        return;
    }

    if (points.size() < 2) {
        emit sigError("[SIG] Waveform points < 2");
        return;
    }

    // ===== 1️⃣ 下载波形 =====
    QStringList list;
    for (int v : points) {
        if (v < 0) v = 0;
        if (v > 16383) v = 16383;
        list << QString::number(v);
    }

    QString cmd = ":TRACe:DATA:DAC VOLATILE," + list.join(",");

    if (!send(cmd)) {
        emit sigError("[SIG] Download DAC failed");
        return;
    }

    emit sigLog("[SIG] Waveform downloaded");

    // ===== 2️⃣ 设置输出 =====
    QString ch = QString::number(channel);

    send(QString(":SOURce%1:FUNCtion USER").arg(ch));
    send(QString(":SOURce%1:FREQuency %2").arg(ch).arg(freq, 0, 'f', 6));
    send(QString(":SOURce%1:VOLTage:UNIT VPP").arg(ch));
    send(QString(":SOURce%1:VOLTage %2").arg(ch).arg(vpp, 0, 'f', 6));
    send(QString(":SOURce%1:VOLTage:OFFSet %2").arg(ch).arg(offset, 0, 'f', 6));
    send(QString(":OUTPut%1 ON").arg(ch));

    emit sigLog("[SIG] USER waveform output enabled");
}

void SigWorker::disconnectDevice()
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

    emit sigLog("[SIG] disconnected");
    emit connectSuccess(connected);
}
