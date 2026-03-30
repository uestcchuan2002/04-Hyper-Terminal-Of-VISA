#ifndef SIGWORKER_H
#define SIGWORKER_H

#include <QObject>
#include <visa.h>
#include <QVector>
class SigWorker : public QObject
{
    Q_OBJECT
public:
    explicit SigWorker(QObject *parent = nullptr);

signals:
    void sigLog(QString msg);
    void sigError(QString msg);
    void connectSuccess(bool connected);

public slots:
    void connectDevice(QString addr);
    void writeCmd(QString cmd);
    void readCmd();
    void disconnectDevice();
    void downloadWave(QVector<int> points,
                          int channel,
                          double freq,
                          double vpp,
                          double offset);

private:
    ViSession rm = VI_NULL;
    ViSession dev = VI_NULL;
    bool connected = false;

    bool send(const QString &cmd);
};

#endif
