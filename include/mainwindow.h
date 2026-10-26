#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSaveClicked();
    void onBrowseClicked();
    void onModeChanged();

private:
    QRadioButton *scriptRadio;
    QRadioButton *commandRadio;
    QLineEdit *inputField;
    QPushButton *browseButton;
    QSpinBox *delaySpinBox;
    QCheckBox *pkexecCheckBox;
    QPushButton *saveButton;
    QLabel *statusLabel;

    void setupUi();
    bool createAutostartEntry(const QString &command, int delay, bool usePkexec);
};

#endif // MAINWINDOW_H
