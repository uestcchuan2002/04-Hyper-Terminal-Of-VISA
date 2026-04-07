#include "mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDateTime>
#include <QByteArray>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>
#include <QtMath>
#include <QThread>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initUi();
    sigThread = new QThread(this);
    rfThread  = new QThread(this);
    mixerThread = new QThread(this);

    sigWorker = new SigWorker();
    rfWorker  = new RFWorker();
    mixerWorker = new MixerWorker();

    sigWorker->moveToThread(sigThread);
    rfWorker->moveToThread(rfThread);
    mixerWorker->moveToThread(mixerThread);

    sigThread->start();
    rfThread->start();
    mixerThread->start();

    // ===== UI → Sig线程 =====
    // 1.信号源-连接-信号与槽
    {
        connect(btnConnect, &QPushButton::clicked, this, &MainWindow::onSigConnectClicked);
        connect(this, &MainWindow::sig_connect, sigWorker, &SigWorker::connectDevice);
        connect(this, &MainWindow::sig_disconnect, sigWorker, &SigWorker::disconnectDevice);
        connect(sigWorker, &SigWorker::connectSuccess, this, &MainWindow::onSigConnectSuccess);
    }

    // 2.信号源-写-信号与槽
    {
        connect(btnWrite, &QPushButton::clicked, this, &MainWindow::onSigWriteClicked);
        connect(this, &MainWindow::sig_write, sigWorker, &SigWorker::writeCmd);
    }

    // 3.信号源-读-信号与槽
    {
        connect(btnRead, &QPushButton::clicked, this, &MainWindow::onSigReadClicked);
        connect(this, &MainWindow::sig_read, sigWorker, &SigWorker::readCmd);
    }

    // 4.信号源-波形下载-信号与槽
    {
        connect(btnLoadFile, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
        connect(btnDownloadWave, &QPushButton::clicked, this, &MainWindow::onDownloadWaveClicked);
        connect(this, &MainWindow::sig_downloadWave, sigWorker, &SigWorker::downloadWave);
    }

    // 5.射频源-连接-信号与槽
    {
        connect(rfBtnConnect, &QPushButton::clicked, this, &MainWindow::onRfConnectClicked);
        connect(this, &MainWindow::rf_connect, rfWorker, &RFWorker::connectDevice);
        connect(this, &MainWindow::rf_disconnect, rfWorker, &RFWorker::disconnectDevice);
        connect(rfWorker, &RFWorker::connectSuccess, this, &MainWindow::onRfConnectSuccess);
    }

    // 6.射频源-写-信号与槽
    {
        connect(rfBtnWrite, &QPushButton::clicked, this, &MainWindow::onRFWriteClicked);
        connect(this, &MainWindow::rf_write, rfWorker, &RFWorker::writeCmd);
    }

    // 7.射频源-读-信号与槽
    {
        connect(rfBtnRead, &QPushButton::clicked, this, &MainWindow::onRFReadClicked);
        connect(this, &MainWindow::rf_read, rfWorker, &RFWorker::readCmd);
    }

    // 8.射频源-开启与关闭-信号与槽
    {
        connect(rfBtnOutputOn, &QPushButton::clicked, this, &MainWindow::onRFOutputOnClicked);
        connect(rfBtnOutputOff, &QPushButton::clicked, this, &MainWindow::onRFOutputOffClicked);
        connect(this, &MainWindow::rf_output, rfWorker, &RFWorker::output);
    }

    // 9.射频源-配置-信号与槽
    {
        connect(rfBtnConfig, &QPushButton::clicked, this, &MainWindow::onRFConfigClicked);
        connect(this, &MainWindow::rf_config, rfWorker, &RFWorker::config);
    }

    // 10.混频器
    {
        // 端口扫描
        connect(this, &MainWindow::sigScanPorts, mixerWorker, &MixerWorker::scanPorts);
        connect(mixerWorker, &MixerWorker::portsUpdated, this, &MainWindow::onPortsUpdated);
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, [=](){ emit sigScanPorts();});
        timer->start(2000);

        // 设备连接
        connect(this, &MainWindow::sigConnectMixer, mixerWorker, &MixerWorker::connectPort);
        connect(this, &MainWindow::sigDisconnectMixer, mixerWorker, &MixerWorker::disconnectPort);
        connect(mixBtnConnect, &QPushButton::clicked, this, &MainWindow::onMixBtnConnectClicked);
        connect(mixerWorker, &MixerWorker::connected, this, [=](bool ok){
            if (ok == true) {
                miIsConnected = true;
                timer->stop();
                mixBtnConnect->setText("Disconnect");
                mixBtnSetFreq->setEnabled(true);
                mixBtnSetDown->setEnabled(true);
                mixBtnSetUp->setEnabled(true);
                mixBtnSend->setEnabled(true);
            } else {
                miIsConnected = false;
                timer->start(2000);
                mixBtnConnect->setText("Connect");
                mixBtnSetFreq->setEnabled(false);
                mixBtnSetDown->setEnabled(false);
                mixBtnSetUp->setEnabled(false);
                mixBtnSend->setEnabled(false);
            }
        }
        );

        // 指令发送
        connect(this, &MainWindow::sigSendMixer, mixerWorker, &MixerWorker::sendCommand);
        connect(this, &MainWindow::sigSetComd, mixerWorker, &MixerWorker::onSetComd);
        connect(mixBtnSend, &QPushButton::clicked, this, &MainWindow::onMixBtnSendClicked);
        connect(mixBtnSetFreq, &QPushButton::clicked, this, &MainWindow::onMixBtnSetFreqClicked);
        connect(mixBtnSetDown, &QPushButton::clicked, this, &MainWindow::onMixBtnSetDownClicked);
        connect(mixBtnSetUp, &QPushButton::clicked, this, &MainWindow::onMixBtnSetUpClicked);
    }

    // ==== 日志信号绑定 ====
    {
        connect(sigWorker, &SigWorker::sigLog,
                this, [=](QString msg){
            log(LOG_SIG, msg);
        });

        connect(sigWorker, &SigWorker::sigError,
                this, [=](QString msg){
            log(LOG_ERROR, msg);
        });

        connect(rfWorker, &RFWorker::rfLog,
                this, [=](QString msg){
            log(LOG_RF, msg);
        });

        connect(rfWorker, &RFWorker::rfError,
                this, [=](QString msg){
            log(LOG_ERROR, msg);
        });

         connect(mixerWorker, &MixerWorker::miLog,
                 this, [=](QString msg){
             log(LOG_MI, msg);
         });

         connect(mixerWorker, &MixerWorker::miError,
                 this, [=](QString msg){
             log(LOG_ERROR, msg);
         });
    }
}

MainWindow::~MainWindow()
{
    // ===== 停止 Sig线程 =====
    if (sigThread) {
        sigThread->quit();   // 让线程退出事件循环
        sigThread->wait();   // 等待线程真正结束
    }

    // ===== 停止 RF线程 =====
    if (rfThread) {
        rfThread->quit();
        rfThread->wait();
    }

    if (mixerThread) {
        mixerThread->quit();   // ⭐ 必须
        mixerThread->wait();   // ⭐ 必须
    }

    delete sigWorker;
    delete rfWorker;
    delete mixerWorker;

    closeVisa();
}

void MainWindow::initUi()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    setWindowTitle("Instrument Control");
    resize(1300, 500);

    // ================= 左侧：信号发生器 =================
    QGroupBox *groupSig = new QGroupBox("Signal Generator", this);

    QLabel *labelAddress = new QLabel("Address", this);
    QLabel *labelCommand = new QLabel("Command", this);
    QLabel *labelFreq    = new QLabel("Freq(Hz)", this);
    QLabel *labelAmp     = new QLabel("Amp(Vpp)", this);
    QLabel *labelOffset  = new QLabel("Offset(V)", this);

    editAddress = new QLineEdit(this);
    editCommand = new QLineEdit(this);
    editFreq    = new QLineEdit(this);
    editAmp     = new QLineEdit(this);
    editOffset  = new QLineEdit(this);

    editAddress->setText("TCPIP0::192.168.2.104::INSTR");
    editCommand->setText("*IDN?");
    editFreq->setText("1000");
    editAmp->setText("2.0");
    editOffset->setText("0.0");

    btnConnect      = new QPushButton("Connect", this);
    btnWrite        = new QPushButton("Write", this);
    btnRead         = new QPushButton("Read", this);
    btnLoadFile     = new QPushButton("Load File", this);
    btnDownloadWave = new QPushButton("Download Arb", this);


    btnWrite->setEnabled(false);
    btnRead->setEnabled(false);
    btnDownloadWave->setEnabled(false);

    QGridLayout *gridSig = new QGridLayout(groupSig);

    gridSig->addWidget(labelAddress, 0, 0);
    gridSig->addWidget(editAddress, 0, 1, 1, 2);
    gridSig->addWidget(btnConnect, 0, 3);

    gridSig->addWidget(labelCommand, 1, 0);
    gridSig->addWidget(editCommand, 1, 1, 1, 3);

    gridSig->addWidget(labelFreq,   2, 0);
    gridSig->addWidget(editFreq,    2, 1);
    gridSig->addWidget(labelAmp,    2, 2);
    gridSig->addWidget(editAmp,     2, 3);

    gridSig->addWidget(labelOffset, 3, 0);
    gridSig->addWidget(editOffset,  3, 1);

    // 按钮区（放在左侧内部）
    QHBoxLayout *sigBtnLayout = new QHBoxLayout;

    // sigBtnLayout->addWidget(btnConnect);
    sigBtnLayout->addWidget(btnWrite);
    sigBtnLayout->addWidget(btnRead);
    sigBtnLayout->addWidget(btnLoadFile);
    sigBtnLayout->addWidget(btnDownloadWave);

    gridSig->addLayout(sigBtnLayout, 4, 0, 1, 4);

    gridSig->setColumnStretch(1, 1);
    gridSig->setColumnStretch(3, 1);
    // gridSig->setRowStretch(3, 1);

    // ================= 右侧：射频信号源 =================
    QGroupBox *groupRF = new QGroupBox("RF Generator", this);

    QLabel *rfLabelAddr   = new QLabel("Address", this);
    QLabel *rfLabelCommand= new QLabel("Command", this);   // ⭐ 新增
    QLabel *rfLabelFreq   = new QLabel("Freq (Hz)", this);
    QLabel *rfLabelPower  = new QLabel("Power (dBm)", this);

    rfEditAddress = new QLineEdit(this);
    rfEditCommand = new QLineEdit(this);   // ⭐ 新增
    rfEditFreq    = new QLineEdit(this);
    rfEditPower   = new QLineEdit(this);

    rfEditAddress->setText("TCPIP0::192.168.2.144::INSTR");
    rfEditCommand->setText("*IDN?");       // ⭐ 默认指令
    rfEditFreq->setText("1000000000");
    rfEditPower->setText("-20");

    rfBtnConnect   = new QPushButton("Connect", this);
    rfBtnWrite     = new QPushButton("Write", this);   // ⭐ 新增
    rfBtnRead      = new QPushButton("Read", this);    // ⭐ 新增
    rfBtnOutputOn  = new QPushButton("Output ON", this);
    rfBtnOutputOff = new QPushButton("Output OFF", this);
    rfBtnConfig = new QPushButton("Config RF", this);


    rfBtnWrite->setEnabled(false);
    rfBtnRead->setEnabled(false);
    rfBtnOutputOn->setEnabled(false);
    rfBtnOutputOff->setEnabled(false);
    rfBtnConfig->setEnabled(false);
    QGridLayout *rfGrid = new QGridLayout(groupRF);

    // ===== 地址 =====
    rfGrid->addWidget(rfLabelAddr,   0, 0);
    rfGrid->addWidget(rfEditAddress,0, 1, 1, 2);
    rfGrid->addWidget(rfBtnConnect, 0, 3);

    // ===== 指令 =====
    rfGrid->addWidget(rfLabelCommand, 1, 0);
    rfGrid->addWidget(rfEditCommand,  1, 1, 1, 3);

    // ===== 频率/功率 =====
    rfGrid->addWidget(rfLabelFreq,  2, 0);
    rfGrid->addWidget(rfEditFreq,   2, 1);

    rfGrid->addWidget(rfLabelPower, 2, 2);
    rfGrid->addWidget(rfEditPower,  2, 3);

    // ===== 按钮区（SCPI + 输出控制）=====
    QHBoxLayout *rfBtnLayout = new QHBoxLayout;
    rfBtnLayout->addWidget(rfBtnWrite);      // ⭐ 新增
    rfBtnLayout->addWidget(rfBtnRead);       // ⭐ 新增
    //rfBtnLayout->addSpacing(20);             // 分隔
    rfBtnLayout->addWidget(rfBtnOutputOn);
    rfBtnLayout->addWidget(rfBtnOutputOff);
    //rfBtnLayout->addSpacing(20);
    rfBtnLayout->addWidget(rfBtnConfig);
    rfGrid->addLayout(rfBtnLayout, 3, 0, 1, 4);

    // 拉伸
    rfGrid->setColumnStretch(1, 1);
    rfGrid->setColumnStretch(3, 1);
    rfGrid->setRowStretch(3, 1);

    // ================= 混频器 =================
    QGroupBox *groupMixer = new QGroupBox("Mixer", this);

    // ===== Label =====
    QLabel *mixLabelPort  = new QLabel("COM Port", this);
    QLabel *mixLabelFreq  = new QLabel("Freq (MHz)", this);
    QLabel *mixLabelDown  = new QLabel("Down Att (dB)", this);
    QLabel *mixLabelUp    = new QLabel("Up Att (dB)", this);
    QLabel *mixLabelCmd   = new QLabel("Command", this);

    // ===== Edit =====
    mixComboPort = new QComboBox(this);
    mixEditFreq  = new QLineEdit(this);
    mixEditIFAtt = new QLineEdit(this);   // Down IF
    mixEditRFAtt = new QLineEdit(this);   // Down RF

    mixEditUpIF  = new QLineEdit(this);   // Up IF
    mixEditUpRF  = new QLineEdit(this);   // Up RF

    mixEditCmd   = new QLineEdit(this);

    // ===== 默认值 =====

    mixEditFreq->setText("1000");
    mixEditIFAtt->setText("10");
    mixEditRFAtt->setText("10");
    mixEditUpIF->setText("10");
    mixEditUpRF->setText("10");
    mixEditCmd->setText("*IDN?");

    // 👉 限制宽度（更像仪器UI）
    mixEditIFAtt->setMaximumWidth(60);
    mixEditRFAtt->setMaximumWidth(60);
    mixEditUpIF->setMaximumWidth(60);
    mixEditUpRF->setMaximumWidth(60);

    // ===== Button =====
    mixBtnConnect = new QPushButton("Connect", this);
    mixBtnSetFreq = new QPushButton("Set", this);
    mixBtnSetDown = new QPushButton("Set", this);
    mixBtnSetUp   = new QPushButton("Set", this);
    mixBtnSend    = new QPushButton("Send", this);

    // ===== 初始状态 =====
    mixBtnSetFreq->setEnabled(false);
    mixBtnSetDown->setEnabled(false);
    mixBtnSetUp->setEnabled(false);
    mixBtnSend->setEnabled(false);

    // ===== Layout =====
    QGridLayout *mixGrid = new QGridLayout(groupMixer);

    // ===== 串口 =====
    mixGrid->addWidget(mixLabelPort, 0, 0);
    mixGrid->addWidget(mixComboPort, 0, 1, 1, 2);
    mixGrid->addWidget(mixBtnConnect, 0, 3);

    // ===== 频率 =====
    mixGrid->addWidget(mixLabelFreq, 1, 0);
    mixGrid->addWidget(mixEditFreq, 1, 1);
    mixGrid->addWidget(new QLabel("(200~1800)", this), 1, 2);
    mixGrid->addWidget(mixBtnSetFreq, 1, 3);

    // ===== 下变频（带 IF/RF 标签）=====
    QHBoxLayout *downLayout = new QHBoxLayout;
    downLayout->addWidget(new QLabel("IF:", this));
    downLayout->addWidget(mixEditIFAtt);
    downLayout->addSpacing(10);
    downLayout->addWidget(new QLabel("RF:", this));
    downLayout->addWidget(mixEditRFAtt);

    mixGrid->addWidget(mixLabelDown, 2, 0);
    mixGrid->addLayout(downLayout, 2, 1, 1, 2);
    mixGrid->addWidget(mixBtnSetDown, 2, 3);

    // ===== 上变频（带 IF/RF 标签）=====
    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->addWidget(new QLabel("IF:", this));
    upLayout->addWidget(mixEditUpIF);
    upLayout->addSpacing(10);
    upLayout->addWidget(new QLabel("RF:", this));
    upLayout->addWidget(mixEditUpRF);

    mixGrid->addWidget(mixLabelUp, 3, 0);
    mixGrid->addLayout(upLayout, 3, 1, 1, 2);
    mixGrid->addWidget(mixBtnSetUp, 3, 3);

    // ===== 指令发送 =====
    mixGrid->addWidget(mixLabelCmd, 4, 0);
    mixGrid->addWidget(mixEditCmd, 4, 1, 1, 2);
    mixGrid->addWidget(mixBtnSend, 4, 3);

    // ===== 拉伸 =====
    mixGrid->setColumnStretch(1, 1);
    mixGrid->setColumnStretch(2, 1);
    mixGrid->setColumnStretch(3, 1);

    // ================= 统一日志区 =================
    QGroupBox *groupLog = new QGroupBox("System Log", this);

    logViewer = new QTextEdit(this);
    logViewer->setReadOnly(true);

    QVBoxLayout *logLayout = new QVBoxLayout(groupLog);
    logLayout->addWidget(logViewer);

    // ================= 总布局（左右结构）=================
    QHBoxLayout *topLayout = new QHBoxLayout;

    topLayout->addWidget(groupSig, 1);
    topLayout->addWidget(groupRF, 1);
    topLayout->addWidget(groupMixer, 1);   // ⭐ 新增

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(topLayout, 3);
    mainLayout->addWidget(groupLog, 5);
}

void MainWindow::onSigConnectClicked()
{
    if (sigConnect == false) {
        emit sig_connect(editAddress->text());
    } else if (sigConnect == true) {
        emit sig_disconnect();
    }
}

void MainWindow::onSigConnectSuccess(bool connected)
{
    if (connected == true) {
        sigConnect = true;
        btnWrite->setEnabled(true);
        btnRead->setEnabled(true);
        btnDownloadWave->setEnabled(true);
        btnConnect->setText("Disconnect");
    } else if (connected == false) {
        sigConnect = false;
        btnConnect->setText("Connect");
    }
}

void MainWindow::onSigWriteClicked()
{
    if (!sigConnect) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    emit sig_write(editCommand->text());

    log(LOG_SIG, "Write request sent.");
}

void MainWindow::onSigReadClicked()
{
    if (!sigConnect) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    emit sig_read();   // ⭐ 交给线程处理

    log(LOG_SIG, "Read request sent.");
}


bool MainWindow::loadWaveFile(const QString &fileName, QVector<double> &samples)
{
    samples.clear();

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        log(LOG_ERROR, "Open file failed: " + fileName);
        return false;
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) {
            continue;
        }

        QStringList parts = line.split(QRegExp("[,;\\s]+"), QString::SkipEmptyParts);
        for (const QString &part : parts) {
            bool ok = false;
            double v = part.toDouble(&ok);
            if (ok) {
                samples.push_back(v);
            }
        }
    }

    file.close();

    if (samples.isEmpty()) {
        log(LOG_ERROR, "No valid numeric samples found.");
        return false;
    }

    log(LOG_SIG, QString("Loaded %1 samples.").arg(samples.size()));
    return true;
}

QVector<int> MainWindow::convertToDac14(const QVector<double> &samples)
{
    QVector<int> out;
    out.reserve(samples.size());

    for (double x : samples) {
        if (x > 1.0) x = 1.0;
        if (x < -1.0) x = -1.0;

        int dac = qRound((x + 1.0) * 16383.0 / 2.0);
        if (dac < 0) dac = 0;
        if (dac > 16383) dac = 16383;

        out.push_back(dac);
    }

    return out;
}

void MainWindow::onLoadFileClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
        this,
        "Open Wave File",
        QString(),
        "Wave Files (*.csv *.txt);;All Files (*.*)"
    );

    if (fileName.isEmpty()) {
        return;
    }

    QVector<double> samples;
    if (!loadWaveFile(fileName, samples)) {
        log(LOG_ERROR, "Load file failed.");
        return;
    }

    m_samples = samples;
    log(LOG_SIG, "Wave file ready.");
}

void MainWindow::onDownloadWaveClicked()
{
    if (!sigConnect) {
        log(LOG_ERROR, "Please connect device first.");
        return;
    }

    if (m_samples.isEmpty()) {
        log(LOG_ERROR, "No wave file loaded.");
        return;
    }

    bool okFreq = false;
    bool okAmp = false;
    bool okOffset = false;

    double freqHz = editFreq->text().trimmed().toDouble(&okFreq);
    double vpp    = editAmp->text().trimmed().toDouble(&okAmp);
    double offset = editOffset->text().trimmed().toDouble(&okOffset);

    if (!okFreq || freqHz <= 0.0) {
        log(LOG_ERROR, "Invalid frequency.");
        return;
    }

    if (!okAmp || vpp <= 0.0) {
        log(LOG_ERROR, "Invalid amplitude.");
        return;
    }

    if (!okOffset) {
        log(LOG_ERROR, "Invalid offset.");
        return;
    }

    // ⭐ 核心：生成 DAC 数据（仍然在UI线程做）
    QVector<int> dacPoints = convertToDac14(m_samples);

    // ⭐ 只把“执行”丢给线程
    emit sig_downloadWave(
        dacPoints,
        1,
        freqHz,
        vpp,
        offset
    );

    log(LOG_SIG, "Download task sent to worker thread.");
}


void MainWindow::closeVisa()
{
    if (!sigConnect)
        return;

    // ⭐ 交给线程去关闭设备
    emit sig_disconnect();

    sigConnect = false;
    log(LOG_SIG, "Disconnect request sent.");
}

void MainWindow::closeVisaRF()
{
    if (!rfIsConnected)
        return;

    // ⭐ 让 RF 线程自己关闭
    emit rf_disconnect();

    rfIsConnected = false;
    log(LOG_RF, "RF disconnect request sent.");
}

void MainWindow::onRfConnectClicked()
{
    if (rfIsConnected == false) {
        emit rf_connect(rfEditAddress->text());
    } else if (rfIsConnected == true) {
        emit rf_disconnect();
    }
}

void MainWindow::onRfConnectSuccess(bool connected)
{
    if (connected == true) {
        rfIsConnected = true;
        rfBtnConnect->setText("Disconnect");
        rfBtnWrite->setEnabled(true);
        rfBtnRead->setEnabled(true);
        rfBtnOutputOn->setEnabled(true);
        rfBtnOutputOff->setEnabled(true);
        rfBtnConfig->setEnabled(true);
    } else if (connected == false) {
        rfIsConnected = false;
        rfBtnConnect->setText("Connect");
    }
}

void MainWindow::onRFWriteClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    emit rf_write(rfEditCommand->text());

    log(LOG_RF, "Write request sent.");
}

void MainWindow::onRFReadClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    emit rf_read();   // ⭐ 交给线程处理

    log(LOG_RF, "Read request sent.");
}


void MainWindow::onRFOutputOnClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    rfBtnOutputOn->setEnabled(false);
    rfBtnOutputOff->setEnabled(true);
    emit rf_output(true);
    log(LOG_RF, "Rf output on.");
}

void MainWindow::onRFOutputOffClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    rfBtnOutputOn->setEnabled(true);
    rfBtnOutputOff->setEnabled(false);
    emit rf_output(false);
    log(LOG_RF, "Rf output off.");
}

void MainWindow::onRFConfigClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    emit rf_config(
        rfEditFreq->text().toDouble(),
        rfEditPower->text().toDouble()
    );
    log(LOG_RF, "Rf config...");
}

void MainWindow::onPortsUpdated(QStringList ports)
{
    mixComboPort->clear();
    mixComboPort->addItems(ports);

    // 可选：自动选中第一个
    if (!ports.isEmpty()) {
        mixComboPort->setCurrentIndex(0);
    }

    log(LOG_MI, "[Mixer] Ports updated");
}

void MainWindow::onMixBtnConnectClicked()
{
    if (miIsConnected == false) {
        emit sigConnectMixer(mixComboPort->currentText());
    } else {
        emit sigDisconnectMixer();
    }
}

void MainWindow::onMixBtnSetFreqClicked()
{
    QString freqStr;
    freqStr =  mixEditFreq->text();
    emit sigSetComd(0, freqStr);
}

void MainWindow::onMixBtnSetDownClicked()
{
    QString down_if;
    QString down_rf;
    down_if = mixEditIFAtt->text();
    down_rf = mixEditRFAtt->text();
    emit sigSetComd(1, down_rf + down_if);
}

void MainWindow::onMixBtnSetUpClicked()
{
    QString up_if;
    QString up_rf;
    up_if = mixEditIFAtt->text();
    up_rf = mixEditRFAtt->text();
    emit sigSetComd(1, up_rf + up_if);
}

void MainWindow::onMixBtnSendClicked()
{
    emit sigSendMixer(mixEditCmd->text());
}


void MainWindow::appendLog(const QString &msg, const QColor &color)
{
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");

    QTextCharFormat format;
    format.setForeground(color);

    QTextCursor cursor = logViewer->textCursor();
    cursor.movePosition(QTextCursor::End);

    cursor.insertText(QString("[%1] %2\n").arg(time, msg), format);

    logViewer->setTextCursor(cursor);
}

void MainWindow::log(LogType type, const QString &msg)
{
    QColor color;

    switch (type)
    {
    case LOG_SIG:   color = QColor(0,102,204); break;
    case LOG_RF:    color = QColor(0,153,0); break;
    case LOG_MI: color = QColor(255, 140, 0); break;  // 橙色
    case LOG_ERROR: color = Qt::red; break;
    }

    appendLog(msg, color);
}
