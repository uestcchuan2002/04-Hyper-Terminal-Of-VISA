#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QTextEdit;
class QPushButton;

#include "visa.h"

enum LogType
{
    LOG_SIG,
    LOG_RF,
    LOG_ERROR
};

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

    void closeVisa();

    bool sendScpi(const QString &cmd);
    bool loadWaveFile(const QString &fileName, QVector<double> &samples);
    QVector<int> convertToDac14(const QVector<double> &samples);
    bool downloadArbDac(const QVector<int> &points);
    bool outputUserWaveform(int channel, double freqHz, double vpp, double offset);

    void onRFConnectClicked();
    bool sendScpiRF(const QString &cmd);
    // 日志接口
    void appendLog(const QString &msg, const QColor &color);
    void log(LogType type, const QString &msg);

private:
    QLineEdit *editAddress;
    QLineEdit *editCommand;

    QLineEdit *editFreq;
    QLineEdit *editAmp;
    QLineEdit *editOffset;


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


    QLineEdit *rfEditCommand;
    QPushButton *rfBtnWrite;
    QPushButton *rfBtnRead;
    QPushButton *rfBtnConfig;

    // ===== RF VISA 连接 =====
    ViSession rfDefaultRM;
    ViSession rfDeviceSession;
    bool rfIsConnected;

    // ===== 日志 =====
    QTextEdit *logViewer;
};

#endif // MAINWINDOW_H
