#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "kstartup_" + QLocale(locale).name();
        if (translator.load(":/translations/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();
    return app.exec();
}
