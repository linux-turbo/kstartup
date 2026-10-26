#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi()
{
    setWindowTitle(tr("KStartup - Delayed Autostart Manager"));
    resize(560, 300);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *modeLayout = new QHBoxLayout();
    scriptRadio = new QRadioButton(tr("Select Script File"), this);
    commandRadio = new QRadioButton(tr("Custom Command"), this);
    scriptRadio->setChecked(true);

    modeLayout->addWidget(scriptRadio);
    modeLayout->addWidget(commandRadio);
    mainLayout->addLayout(modeLayout);

    QFormLayout *formLayout = new QFormLayout();

    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputField = new QLineEdit(this);
    inputField->setPlaceholderText(tr("Select a script or type a command..."));
    
    browseButton = new QPushButton(tr("Browse..."), this);
    inputLayout->addWidget(inputField);
    inputLayout->addWidget(browseButton);

    formLayout->addRow(tr("Target:"), inputLayout);

    delaySpinBox = new QSpinBox(this);
    delaySpinBox->setRange(0, 60);
    delaySpinBox->setSuffix(tr(" second(s)"));
    delaySpinBox->setValue(5);
    formLayout->addRow(tr("Startup delay:"), delaySpinBox);

    pkexecCheckBox = new QCheckBox(tr("Run with Root privileges (pkexec)"), this);
    formLayout->addRow(pkexecCheckBox);

    mainLayout->addLayout(formLayout);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    saveButton = new QPushButton(tr("Add to Autostart"), this);
    buttonLayout->addWidget(saveButton);

    mainLayout->addLayout(buttonLayout);

    statusLabel = new QLabel(this);
    mainLayout->addWidget(statusLabel);

    setCentralWidget(centralWidget);

    connect(scriptRadio, &QRadioButton::toggled, this, &MainWindow::onModeChanged);
    connect(browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseClicked);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSaveClicked);
    
    onModeChanged();
}

void MainWindow::onModeChanged()
{
    if (scriptRadio->isChecked()) {
        browseButton->setEnabled(true);
        inputField->setPlaceholderText(tr("e.g. /home/user/myscript.sh"));
    } else {
        browseButton->setEnabled(false);
        inputField->setPlaceholderText(tr("e.g. mpv /home/user/sound.wav or flatpak run com.spotify.Client"));
    }
}

void MainWindow::onBrowseClicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Select Script"),
        QDir::homePath(),
        tr("All Files (*);;Shell Scripts (*.sh);;Python Scripts (*.py)")
    );

    if (!filePath.isEmpty()) {
        inputField->setText(filePath);
    }
}

void MainWindow::onSaveClicked()
{
    QString target = inputField->text().trimmed();
    int delay = delaySpinBox->value();
    bool usePk = pkexecCheckBox->isChecked();

    if (target.isEmpty()) {
        QMessageBox::warning(this, tr("Error"), tr("Please provide a valid script path or command."));
        return;
    }

    if (createAutostartEntry(target, delay, usePk)) {
        QMessageBox::information(this, tr("Success"), tr("Successfully added to autostart!"));
        inputField->clear();
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Failed to create autostart entry."));
    }
}

bool MainWindow::createAutostartEntry(const QString &command, int delay, bool usePkexec)
{
    QString autostartDir = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "/autostart";
    QDir dir(autostartDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    qint64 timestamp = QDateTime::currentMSecsSinceEpoch();
    QString filename = QString("%1/kstartup-%2.desktop").arg(autostartDir).arg(timestamp);
    
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);

    QString finalCmd = command;
    if (usePkexec) {
        finalCmd = "pkexec " + finalCmd;
    }
    if (delay > 0) {
        finalCmd = QString("sh -c \"sleep %1 && %2\"").arg(delay).arg(finalCmd);
    }

    out << "[Desktop Entry]\n";
    out << "Type=Application\n";
    out << "Name=KStartup Task (" << QString::number(timestamp) << ")\n";
    out << "Exec=" << finalCmd << "\n";
    out << "Hidden=false\n";
    out << "NoDisplay=false\n";
    out << "X-GNOME-Autostart-enabled=true\n";

    file.close();
    return true;
}
