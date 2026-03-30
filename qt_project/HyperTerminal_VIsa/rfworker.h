#ifndef RFWORKER_H
#define RFWORKER_H

#include <QObject>
#include <visa.h>

class RFWorker : public QObject
{
    Q_OBJECT
public:
    explicit RFWorker(QObject *parent = nullptr);

signals:
    void rfLog(QString msg);
    void rfError(QString msg);
    void connectSuccess(bool connected);

public slots:
    void connectDevice(QString addr);
    void disconnectDevice();
    void writeCmd(QString cmd);
    void readCmd();
    void output(bool on);
    void config(double freq, double power);


private:
    ViSession rm = VI_NULL;
    ViSession dev = VI_NULL;
    bool connected = false;

    bool send(const QString &cmd);
};

#endif
