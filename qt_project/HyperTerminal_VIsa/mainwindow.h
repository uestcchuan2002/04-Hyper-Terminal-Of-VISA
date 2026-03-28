#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QTextEdit;
class QPushButton;

#include "visa.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnectClicked();
    void onWriteClicked();
    void onReadClicked();
    void onExitClicked();
    void onLoadFileClicked();
    void onDownloadWaveClicked();
    void closeVisaRF();
    void onRFWriteClicked();
    void onRFReadClicked();
    void onRFOutputOnClicked();
    void onRFOutputOffClicked();
    void onRFConfigClicked();

private:
    void initUi();
    void appendMessage(const QString &msg);
    void closeVisa();

    bool sendScpi(const QString &cmd);
    bool loadWaveFile(const QString &fileName, QVector<double> &samples);
    QVector<int> convertToDac14(const QVector<double> &samples);
    bool downloadArbDac(const QVector<int> &points);
    bool outputUserWaveform(int channel, double freqHz, double vpp, double offset);
    void appendRFMessage(const QString &msg);
    void onRFConnectClicked();
    bool sendScpiRF(const QString &cmd);

private:
    QLineEdit *editAddress;
    QLineEdit *editCommand;

    QLineEdit *editFreq;
    QLineEdit *editAmp;
    QLineEdit *editOffset;

    QTextEdit *textReturn;
    QPushButton *btnConnect;
    QPushButton *btnWrite;
    QPushButton *btnRead;


    QPushButton *btnLoadFile;
    QPushButton *btnDownloadWave;
    QPushButton *btnExit;

    ViSession defaultRM;
    ViSession deviceSession;
    bool isConnected;

    QVector<double> m_samples;

    // ===== 射频信号源控件 =====
    QLineEdit *rfEditAddress;
    QLineEdit *rfEditFreq;
    QLineEdit *rfEditPower;

    QPushButton *rfBtnConnect;
    QPushButton *rfBtnOutputOn;
    QPushButton *rfBtnOutputOff;
    QTextEdit *rfTextReturn;

    QLineEdit *rfEditCommand;
    QPushButton *rfBtnWrite;
    QPushButton *rfBtnRead;
    QPushButton *rfBtnConfig;

    // ===== RF VISA 连接 =====
    ViSession rfDefaultRM;
    ViSession rfDeviceSession;
    bool rfIsConnected;
};

#endif // MAINWINDOW_H
