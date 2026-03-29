#include "mainwindow.h"

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      editAddress(nullptr),
      editCommand(nullptr),
      editFreq(nullptr),
      editAmp(nullptr),
      editOffset(nullptr),
      btnConnect(nullptr),
      btnWrite(nullptr),
      btnRead(nullptr),
      btnLoadFile(nullptr),
      btnDownloadWave(nullptr),
      btnExit(nullptr),
      defaultRM(VI_NULL),
      deviceSession(VI_NULL),
      isConnected(false),
      rfDefaultRM(VI_NULL),
      rfDeviceSession(VI_NULL),
      rfIsConnected(false)
{
    initUi();
}

MainWindow::~MainWindow()
{
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
    btnExit         = new QPushButton("Exit", this);

    btnWrite->setEnabled(false);
    btnRead->setEnabled(false);
    btnDownloadWave->setEnabled(false);

    QGridLayout *gridSig = new QGridLayout(groupSig);

    gridSig->addWidget(labelAddress, 0, 0);
    gridSig->addWidget(editAddress, 0, 1, 1, 3);

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

    sigBtnLayout->addWidget(btnConnect);
    sigBtnLayout->addWidget(btnWrite);
    sigBtnLayout->addWidget(btnRead);
    sigBtnLayout->addWidget(btnLoadFile);
    sigBtnLayout->addWidget(btnDownloadWave);
    sigBtnLayout->addWidget(btnExit);


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

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(topLayout, 3);
    mainLayout->addWidget(groupLog, 2);

    // ================= 原有信号源信号槽 =================
    connect(btnConnect, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(btnWrite, &QPushButton::clicked, this, &MainWindow::onWriteClicked);
    connect(btnRead, &QPushButton::clicked, this, &MainWindow::onReadClicked);
    connect(btnLoadFile, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
    connect(btnDownloadWave, &QPushButton::clicked, this, &MainWindow::onDownloadWaveClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainWindow::onExitClicked);

    // ⚠ RF 暂时不绑定逻辑（你要求的）
    connect(rfBtnConnect, &QPushButton::clicked,this, &MainWindow::onRFConnectClicked);
    connect(rfBtnWrite, &QPushButton::clicked,this, &MainWindow::onRFWriteClicked);
    connect(rfBtnRead, &QPushButton::clicked,this, &MainWindow::onRFReadClicked);
    connect(rfBtnOutputOn, &QPushButton::clicked,
            this, &MainWindow::onRFOutputOnClicked);
    connect(rfBtnOutputOff, &QPushButton::clicked,
            this, &MainWindow::onRFOutputOffClicked);
    connect(rfBtnConfig, &QPushButton::clicked,
            this, &MainWindow::onRFConfigClicked);
}



void MainWindow::closeVisa()
{
    if (deviceSession != VI_NULL) {
        viClose(deviceSession);
        deviceSession = VI_NULL;
    }

    if (defaultRM != VI_NULL) {
        viClose(defaultRM);
        defaultRM = VI_NULL;
    }

    isConnected = false;
    btnWrite->setEnabled(false);
    btnRead->setEnabled(false);
    btnDownloadWave->setEnabled(false);
    btnConnect->setText("Connect");
}

void MainWindow::onConnectClicked()
{
    if (isConnected) {
        log(LOG_SIG, "Disconnect device.");
        closeVisa();
        return;
    }

    QString address = editAddress->text().trimmed();
    if (address.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Address is empty.");
        log(LOG_ERROR, "Address is empty.");
        return;
    }

    ViStatus status = viOpenDefaultRM(&defaultRM);
    if (status < VI_SUCCESS) {
        log(LOG_ERROR, QString("viOpenDefaultRM failed: %1").arg(status));
        closeVisa();
        return;
    }

    QByteArray addr = address.toLocal8Bit();
    status = viOpen(defaultRM, (ViRsrc)addr.data(), VI_NULL, VI_NULL, &deviceSession);
    if (status < VI_SUCCESS) {
        log(LOG_ERROR, QString("viOpen failed: %1").arg(status));
        closeVisa();
        return;
    }

    viSetAttribute(deviceSession, VI_ATTR_TMO_VALUE, 3000);

    isConnected = true;
    btnWrite->setEnabled(true);
    btnRead->setEnabled(true);
    btnDownloadWave->setEnabled(true);
    btnConnect->setText("Disconnect");

    log(LOG_SIG, "Connect success.");
}

bool MainWindow::sendScpi(const QString &cmd)
{
    if (!isConnected || deviceSession == VI_NULL) {
        log(LOG_ERROR, "Device not connected.");
        return false;
    }

    QByteArray data = cmd.toLocal8Bit();
    if (!data.endsWith('\n')) {
        data.append('\n');
    }

    ViUInt32 writeCount = 0;
    ViStatus status = viWrite(deviceSession,
                              (ViBuf)data.data(),
                              (ViUInt32)data.size(),
                              &writeCount);

    if (status < VI_SUCCESS) {
        log(LOG_ERROR, QString("SCPI send failed: %1").arg(status));
        log(LOG_ERROR, "CMD: " + cmd);
        return false;
    }

    log(LOG_SIG, "SCPI >> " + cmd);
    return true;
}

void MainWindow::onWriteClicked()
{
    QString cmd = editCommand->text().trimmed();
    if (cmd.isEmpty()) {
        log(LOG_ERROR, "Command is empty.");
        return;
    }

    sendScpi(cmd);
}

void MainWindow::onReadClicked()
{
    if (!isConnected || deviceSession == VI_NULL) {
        log(LOG_ERROR, "Device not connected.");
        return;
    }

    unsigned char buffer[2048] = {0};
    ViUInt32 readCount = 0;

    ViStatus status = viRead(deviceSession, buffer, sizeof(buffer) - 1, &readCount);
    if (status < VI_SUCCESS) {
        if (status == VI_ERROR_TMO) {
            log(LOG_ERROR, "Read timeout.");
        } else {
            log(LOG_ERROR, QString("Read failed: %1").arg(status));
        }
        return;
    }

    buffer[readCount] = '\0';
    QString reply = QString::fromLatin1(reinterpret_cast<const char*>(buffer)).trimmed();
    log(LOG_SIG, "Read << " + reply);
}

void MainWindow::onExitClicked()
{
    close();
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

bool MainWindow::downloadArbDac(const QVector<int> &points)
{
    if (points.size() < 2) {
        log(LOG_ERROR, "Waveform points must be at least 2.");
        return false;
    }

    QStringList list;
    list.reserve(points.size());

    for (int v : points) {
        int dac = v;
        if (dac < 0) dac = 0;
        if (dac > 16383) dac = 16383;
        list << QString::number(dac);
    }

    QString cmd = ":TRACe:DATA:DAC VOLATILE," + list.join(",");
    return sendScpi(cmd);
}

bool MainWindow::outputUserWaveform(int channel, double freqHz, double vpp, double offset)
{
    QString ch = QString::number(channel);

    if (!sendScpi(QString(":SOURce%1:FUNCtion USER").arg(ch))) {
        return false;
    }

    if (!sendScpi(QString(":SOURce%1:FREQuency %2")
                  .arg(ch)
                  .arg(freqHz, 0, 'f', 6))) {
        return false;
    }

    if (!sendScpi(QString(":SOURce%1:VOLTage:UNIT VPP").arg(ch))) {
        return false;
    }

    if (!sendScpi(QString(":SOURce%1:VOLTage %2")
                  .arg(ch)
                  .arg(vpp, 0, 'f', 6))) {
        return false;
    }

    if (!sendScpi(QString(":SOURce%1:VOLTage:OFFSet %2")
                  .arg(ch)
                  .arg(offset, 0, 'f', 6))) {
        return false;
    }

    if (!sendScpi(QString(":OUTPut%1 ON").arg(ch))) {
        return false;
    }

    log(LOG_SIG, "USER waveform output enabled.");
    return true;
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
    if (!isConnected) {
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
    double vpp = editAmp->text().trimmed().toDouble(&okAmp);
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

    QVector<int> dacPoints = convertToDac14(m_samples);

    if (!downloadArbDac(dacPoints)) {
        log(LOG_ERROR, "Download arb data failed.");
        return;
    }

    if (!outputUserWaveform(1, freqHz, vpp, offset)) {
        log(LOG_ERROR, "Enable USER waveform failed.");
        return;
    }

    log(LOG_SIG, QString("Arbitrary waveform downloaded. Freq=%1 Hz, Amp=%2 Vpp, Offset=%3 V")
                  .arg(freqHz)
                  .arg(vpp)
                  .arg(offset));
}

void MainWindow::closeVisaRF()
{
    if (rfDeviceSession != VI_NULL) {
        viClose(rfDeviceSession);
        rfDeviceSession = VI_NULL;
    }

    if (rfDefaultRM != VI_NULL) {
        viClose(rfDefaultRM);
        rfDefaultRM = VI_NULL;
    }

    rfIsConnected = false;

    rfBtnWrite->setEnabled(false);
    rfBtnRead->setEnabled(false);
    rfBtnConnect->setText("Connect");
}



void MainWindow::onRFConnectClicked()
{
    if (rfIsConnected) {
        log(LOG_RF, "Disconnect RF device.");
        closeVisaRF();
        return;
    }

    QString ip = rfEditAddress->text().trimmed();
    if (ip.isEmpty()) {
        QMessageBox::warning(this, "Warning", "RF IP is empty.");
        log(LOG_ERROR, "RF IP is empty.");
        return;
    }

    // ⚠ RF 一般用 TCPIP0::IP::INSTR 格式
    QString address = rfEditAddress->text().trimmed();

    ViStatus status = viOpenDefaultRM(&rfDefaultRM);
    if (status < VI_SUCCESS) {
        log(LOG_ERROR, QString("viOpenDefaultRM failed: %1").arg(status));
        closeVisaRF();
        return;
    }

    QByteArray addr = address.toLocal8Bit();

    status = viOpen(rfDefaultRM,
                    (ViRsrc)addr.data(),
                    VI_NULL,
                    VI_NULL,
                    &rfDeviceSession);

    if (status < VI_SUCCESS) {
        log(LOG_ERROR, QString("viOpen failed: %1").arg(status));
        closeVisaRF();
        return;
    }

    viSetAttribute(rfDeviceSession, VI_ATTR_TMO_VALUE, 3000);

    rfIsConnected = true;

    rfBtnWrite->setEnabled(true);
    rfBtnRead->setEnabled(true);
    rfBtnOutputOn->setEnabled(true);
    rfBtnOutputOff->setEnabled(true);
    rfBtnConfig->setEnabled(true);
    rfBtnConnect->setText("Disconnect");

    log(LOG_RF, "RF Connect success.");
}

bool MainWindow::sendScpiRF(const QString &cmd)
{
    if (!rfIsConnected || rfDeviceSession == VI_NULL) {
        log(LOG_ERROR, "RF device not connected.");
        return false;
    }

    QByteArray data = cmd.toLocal8Bit();

    // SCPI 必须以 \n 结尾
    if (!data.endsWith('\n')) {
        data.append('\n');
    }

    ViUInt32 writeCount = 0;

    ViStatus status = viWrite(rfDeviceSession,
                              (ViBuf)data.data(),
                              (ViUInt32)data.size(),
                              &writeCount);

    if (status < VI_SUCCESS) {
        log(LOG_ERROR, QString("RF SCPI send failed: %1").arg(status));
        log(LOG_ERROR, "CMD: " + cmd);
        return false;
    }

    log(LOG_RF, "RF >> " + cmd);
    return true;
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
    case LOG_ERROR: color = Qt::red; break;
    }

    appendLog(msg, color);
}

void MainWindow::onRFWriteClicked()
{
    QString cmd = rfEditCommand->text().trimmed();

    if (cmd.isEmpty()) {
        log(LOG_ERROR, "Command is empty.");
        return;
    }

    sendScpiRF(cmd);
}

void MainWindow::onRFReadClicked()
{
    if (!rfIsConnected || rfDeviceSession == VI_NULL) {
        log(LOG_ERROR, "RF device not connected.");
        return;
    }

    unsigned char buffer[2048] = {0};
    ViUInt32 readCount = 0;

    ViStatus status = viRead(rfDeviceSession,
                             buffer,
                             sizeof(buffer) - 1,
                             &readCount);

    if (status < VI_SUCCESS) {
        if (status == VI_ERROR_TMO) {
            log(LOG_ERROR, "RF Read timeout.");
        } else {
            log(LOG_ERROR, QString("RF Read failed: %1").arg(status));
        }
        return;
    }

    buffer[readCount] = '\0';

    QString reply = QString::fromLatin1(
                        reinterpret_cast<const char*>(buffer))
                        .trimmed();

    log(LOG_RF, "RF << " + reply);
}


void MainWindow::onRFOutputOnClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "RF device not connected.");
        return;
    }

    if (!sendScpiRF(":OUTP ON")) {
        log(LOG_ERROR, "RF Output ON failed.");
        return;
    }

    log(LOG_RF, "RF Output ON.");
}

void MainWindow::onRFOutputOffClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "RF device not connected.");
        return;
    }

    if (!sendScpiRF(":OUTP OFF")) {
        log(LOG_ERROR, "RF Output OFF failed.");
        return;
    }

    log(LOG_RF, "RF Output OFF.");
}

void MainWindow::onRFConfigClicked()
{
    if (!rfIsConnected) {
        log(LOG_ERROR, "RF device not connected.");
        return;
    }

    bool okFreq = false;
    bool okPower = false;

    double freq = rfEditFreq->text().trimmed().toDouble(&okFreq);
    double power = rfEditPower->text().trimmed().toDouble(&okPower);

    if (!okFreq || freq <= 0) {
        log(LOG_ERROR, "Invalid frequency.");
        return;
    }

    if (!okPower) {
        log(LOG_ERROR, "Invalid power.");
        return;
    }

    log(LOG_RF, "Start RF configuration...");

    // 1️⃣ 查询设备
    sendScpiRF("*IDN?");
    onRFReadClicked();

    // 2️⃣ 恢复出厂设置
    if (!sendScpiRF(":SYST:PRES:TYPE FAC")) return;
    if (!sendScpiRF(":SYST:PRES")) return;

    // 3️⃣ 设置频率（Hz）
    if (!sendScpiRF(QString(":FREQ %1").arg(freq, 0, 'f', 0))) return;

    // 4️⃣ 设置功率（dBm）
    if (!sendScpiRF(QString(":LEV %1").arg(power, 0, 'f', 2))) return;

    // 5️⃣ 打开输出
    if (!sendScpiRF(":OUTP ON")) return;

    log(LOG_RF, "RF configuration done.");
}
