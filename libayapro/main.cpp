#include "mainwindow.h"
#include "global.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss(":/res/style/stylesheet.qss");
    if(qss.open(QFile::ReadOnly)){
        qDebug("Open Success!");
        QString style = QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("Open Failed!");
    }

    QString filename = "config.ini";
    QString app_path = QCoreApplication::applicationDirPath();
    QString config_path = QDir::toNativeSeparators(app_path + QDir::separator() + filename);
    QSettings setting(config_path,QSettings::IniFormat);
    QString gate_host = setting.value("GateServer/host").toString();
    QString gate_port = setting.value("GateServer/port").toString();
    gate_url_prefix = "http://" + gate_host + ":" + gate_port;

    MainWindow w;
    w.show();
    return a.exec();
}
