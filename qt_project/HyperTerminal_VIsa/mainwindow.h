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

private:
    void initUi();
    void appendMessage(const QString &msg);
    void closeVisa();

    bool sendScpi(const QString &cmd);
    bool loadWaveFile(const QString &fileName, QVector<double> &samples);
    QVector<int> convertToDac14(const QVector<double> &samples);
    bool downloadArbDac(const QVector<int> &points);
    bool outputUserWaveform(int channel, double freqHz, double vpp, double offset);

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
    QPushButton *btnExit;

    QPushButton *btnLoadFile;
    QPushButton *btnDownloadWave;

    ViSession defaultRM;
    ViSession deviceSession;
    bool isConnected;

    QVector<double> m_samples;
};

#endif // MAINWINDOW_H
