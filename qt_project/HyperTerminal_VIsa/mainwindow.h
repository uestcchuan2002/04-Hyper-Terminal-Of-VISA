#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QTextEdit;
class QPushButton;

#include "visa.h"
#include "rfworker.h"
#include "sigworker.h"
#include "mixerworker.h"
#include <QComboBox>

enum LogType
{
    LOG_SIG,
    LOG_RF,
    LOG_MI,
    LOG_ERROR
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

// ==== 信号发送器 =====
private slots:
    void onSigConnectClicked();
    void onSigConnectSuccess(bool connected);
    void onSigWriteClicked();
    void onSigReadClicked();
    void onLoadFileClicked();
    void onDownloadWaveClicked();

private:
    bool sigConnect = false;

signals:
    void sig_connect(QString);
    void sig_disconnect(void);
    void sig_write(QString);
    void sig_read();
    void sig_downloadWave(QVector<int>, int, double, double, double);
// ==== 信号发送器 =====

// ==== 射频信号源 =====
private slots:
    void onRfConnectClicked();
    void onRfConnectSuccess(bool connected);
    void onRFWriteClicked();
    void onRFReadClicked();
    void onRFOutputOnClicked();
    void onRFOutputOffClicked();
    void onRFConfigClicked();
private:
    bool rfIsConnected = false;
signals:
    void rf_connect(QString);
    void rf_disconnect();
    void rf_write(QString);
    void rf_read();
    void rf_output(bool);
    void rf_config(double, double);
// ==== 射频信号源 =====

// ==== 混频器 =====
private slots:
    void onPortsUpdated(QStringList ports);
    void onMixBtnConnectClicked();
    void onMixBtnSetFreqClicked();
    void onMixBtnSetDownClicked();
    void onMixBtnSetUpClicked();
    void onMixBtnSendClicked();
private:
    bool miIsConnected = false;
signals:
    void sigScanPorts();
    void sigConnectMixer(QString port);
    void sigDisconnectMixer();
    void sigSendMixer(QString cmd);
    void sigSetComd(int cmd, QString num);
// ==== 混频器 =====

private slots:
    void closeVisaRF();

private:
    void initUi();

    void closeVisa();

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
    // ===== 信号源控件 =====
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


    // ===== Mixer =====
    QComboBox *mixComboPort;   // 替换 mixEditPort
    QLineEdit *mixEditFreq;
    QLineEdit *mixEditIFAtt;
    QLineEdit *mixEditRFAtt;
    QLineEdit *mixEditUpIF;
    QLineEdit *mixEditUpRF;
    QLineEdit *mixEditCmd;   // ⭐ 新增

    QPushButton *mixBtnConnect;
    QPushButton *mixBtnSetFreq;
    QPushButton *mixBtnSetDown;
    QPushButton *mixBtnSetUp;
    QPushButton *mixBtnSend;

    // ===== 日志 =====
    QTextEdit *logViewer;

    // ===== 设备线程 ====
    QThread *sigThread;
    QThread *rfThread;
    QThread *mixerThread;

    SigWorker *sigWorker;
    RFWorker  *rfWorker;
    MixerWorker *mixerWorker;

signals:


    // ===== RF线程 =====









};



#endif // MAINWINDOW_H
