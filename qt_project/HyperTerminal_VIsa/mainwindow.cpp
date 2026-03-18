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
      textReturn(nullptr),
      btnConnect(nullptr),
      btnWrite(nullptr),
      btnRead(nullptr),
      btnLoadFile(nullptr),
      btnDownloadWave(nullptr),
      btnExit(nullptr),
      defaultRM(VI_NULL),
      deviceSession(VI_NULL),
      isConnected(false)
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

    setWindowTitle("DemoForDG");
    resize(780, 360);

    QGroupBox *groupComm = new QGroupBox(this);
    QGroupBox *groupBtns = new QGroupBox(this);

    QLabel *labelAddress = new QLabel("Address", this);
    QLabel *labelCommand = new QLabel("Command", this);
    QLabel *labelFreq    = new QLabel("Freq(Hz)", this);
    QLabel *labelAmp     = new QLabel("Amp(Vpp)", this);
    QLabel *labelOffset  = new QLabel("Offset(V)", this);
    QLabel *labelReturn  = new QLabel("Return", this);

    editAddress = new QLineEdit(this);
    editCommand = new QLineEdit(this);
    editFreq    = new QLineEdit(this);
    editAmp     = new QLineEdit(this);
    editOffset  = new QLineEdit(this);
    textReturn  = new QTextEdit(this);

    editAddress->setText("TCPIP0::192.168.2.104::INSTR");
    editCommand->setText("*IDN?");
    editFreq->setText("1000");
    editAmp->setText("2.0");
    editOffset->setText("0.0");
    textReturn->setReadOnly(true);

    btnConnect      = new QPushButton("Connect", this);
    btnWrite        = new QPushButton("Write", this);
    btnRead         = new QPushButton("Read", this);
    btnLoadFile     = new QPushButton("Load File", this);
    btnDownloadWave = new QPushButton("Download Arb", this);
    btnExit         = new QPushButton("Exit", this);

    btnWrite->setEnabled(false);
    btnRead->setEnabled(false);
    btnDownloadWave->setEnabled(false);

    QGridLayout *grid = new QGridLayout(groupComm);
    grid->addWidget(labelAddress, 0, 0);
    grid->addWidget(editAddress, 0, 1, 1, 3);

    grid->addWidget(labelCommand, 1, 0);
    grid->addWidget(editCommand, 1, 1, 1, 3);

    grid->addWidget(labelFreq,   2, 0);
    grid->addWidget(editFreq,    2, 1);
    grid->addWidget(labelAmp,    2, 2);
    grid->addWidget(editAmp,     2, 3);

    grid->addWidget(labelOffset, 3, 0);
    grid->addWidget(editOffset,  3, 1);

    grid->addWidget(labelReturn, 4, 0);
    grid->addWidget(textReturn,  4, 1, 1, 3);

    grid->setColumnStretch(1, 1);
    grid->setColumnStretch(3, 1);
    grid->setRowStretch(4, 1);

    QVBoxLayout *btnLayout = new QVBoxLayout(groupBtns);
    btnLayout->addWidget(btnConnect);
    btnLayout->addWidget(btnWrite);
    btnLayout->addWidget(btnRead);
    btnLayout->addWidget(btnLoadFile);
    btnLayout->addWidget(btnDownloadWave);
    btnLayout->addWidget(btnExit);
    btnLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    mainLayout->addWidget(groupComm, 1);
    mainLayout->addWidget(groupBtns);

    connect(btnConnect, &QPushButton::clicked, this, &MainWindow::onConnectClicked);
    connect(btnWrite, &QPushButton::clicked, this, &MainWindow::onWriteClicked);
    connect(btnRead, &QPushButton::clicked, this, &MainWindow::onReadClicked);
    connect(btnLoadFile, &QPushButton::clicked, this, &MainWindow::onLoadFileClicked);
    connect(btnDownloadWave, &QPushButton::clicked, this, &MainWindow::onDownloadWaveClicked);
    connect(btnExit, &QPushButton::clicked, this, &MainWindow::onExitClicked);
}

void MainWindow::appendMessage(const QString &msg)
{
    QString time = QDateTime::currentDateTime().toString("HH:mm:ss");
    textReturn->append(QString("[%1] %2").arg(time, msg));
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
        appendMessage("Disconnect device.");
        closeVisa();
        return;
    }

    QString address = editAddress->text().trimmed();
    if (address.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Address is empty.");
        return;
    }

    ViStatus status = viOpenDefaultRM(&defaultRM);
    if (status < VI_SUCCESS) {
        appendMessage(QString("viOpenDefaultRM failed: %1").arg(status));
        closeVisa();
        return;
    }

    QByteArray addr = address.toLocal8Bit();
    status = viOpen(defaultRM, (ViRsrc)addr.data(), VI_NULL, VI_NULL, &deviceSession);
    if (status < VI_SUCCESS) {
        appendMessage(QString("viOpen failed: %1").arg(status));
        closeVisa();
        return;
    }

    viSetAttribute(deviceSession, VI_ATTR_TMO_VALUE, 3000);

    isConnected = true;
    btnWrite->setEnabled(true);
    btnRead->setEnabled(true);
    btnDownloadWave->setEnabled(true);
    btnConnect->setText("Disconnect");

    appendMessage("Connect success.");
}

bool MainWindow::sendScpi(const QString &cmd)
{
    if (!isConnected || deviceSession == VI_NULL) {
        appendMessage("Device not connected.");
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
        appendMessage(QString("SCPI send failed: %1").arg(status));
        appendMessage("CMD: " + cmd);
        return false;
    }

    appendMessage("SCPI >> " + cmd);
    return true;
}

void MainWindow::onWriteClicked()
{
    QString cmd = editCommand->text().trimmed();
    if (cmd.isEmpty()) {
        appendMessage("Command is empty.");
        return;
    }

    sendScpi(cmd);
}

void MainWindow::onReadClicked()
{
    if (!isConnected || deviceSession == VI_NULL) {
        appendMessage("Device not connected.");
        return;
    }

    unsigned char buffer[2048] = {0};
    ViUInt32 readCount = 0;

    ViStatus status = viRead(deviceSession, buffer, sizeof(buffer) - 1, &readCount);
    if (status < VI_SUCCESS) {
        if (status == VI_ERROR_TMO) {
            appendMessage("Read timeout.");
        } else {
            appendMessage(QString("Read failed: %1").arg(status));
        }
        return;
    }

    buffer[readCount] = '\0';
    QString reply = QString::fromLatin1(reinterpret_cast<const char*>(buffer)).trimmed();
    appendMessage("Read << " + reply);
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
        appendMessage("Open file failed: " + fileName);
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
        appendMessage("No valid numeric samples found.");
        return false;
    }

    appendMessage(QString("Loaded %1 samples.").arg(samples.size()));
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
        appendMessage("Waveform points must be at least 2.");
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

    appendMessage("USER waveform output enabled.");
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
        appendMessage("Load file failed.");
        return;
    }

    m_samples = samples;
    appendMessage("Wave file ready.");
}

void MainWindow::onDownloadWaveClicked()
{
    if (!isConnected) {
        appendMessage("Please connect device first.");
        return;
    }

    if (m_samples.isEmpty()) {
        appendMessage("No wave file loaded.");
        return;
    }

    bool okFreq = false;
    bool okAmp = false;
    bool okOffset = false;

    double freqHz = editFreq->text().trimmed().toDouble(&okFreq);
    double vpp = editAmp->text().trimmed().toDouble(&okAmp);
    double offset = editOffset->text().trimmed().toDouble(&okOffset);

    if (!okFreq || freqHz <= 0.0) {
        appendMessage("Invalid frequency.");
        return;
    }

    if (!okAmp || vpp <= 0.0) {
        appendMessage("Invalid amplitude.");
        return;
    }

    if (!okOffset) {
        appendMessage("Invalid offset.");
        return;
    }

    QVector<int> dacPoints = convertToDac14(m_samples);

    if (!downloadArbDac(dacPoints)) {
        appendMessage("Download arb data failed.");
        return;
    }

    if (!outputUserWaveform(1, freqHz, vpp, offset)) {
        appendMessage("Enable USER waveform failed.");
        return;
    }

    appendMessage(QString("Arbitrary waveform downloaded. Freq=%1 Hz, Amp=%2 Vpp, Offset=%3 V")
                  .arg(freqHz)
                  .arg(vpp)
                  .arg(offset));
}
