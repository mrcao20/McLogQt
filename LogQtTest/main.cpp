#include <QApplication>

#include <qdebug.h>
#include <QWidget>

#include <Property/McPropertyConfigurator.h>
#include <McLogManager.h>
#include <QFileInfo>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    McLog::McPropertyConfigurator::defaultConfigure();
    McLog::McPropertyConfigurator::configure("E:/QtCreator/McLogQt/LogQtTest/init.ini");
    McLog::McLogManager::installQtMessageHandler();
    QDir dir("./log");
    auto strs = dir.entryList(QDir::Files, QDir::Time);
    qInfo() << strs;
    QFileInfo info("./log/.gat.gz");
    qCritical() << "aaaa";
    qWarning() << info.baseName()
             << info.completeSuffix();
//    for(int i = 0; i < 10000; ++i){
//        QString a = ":Lidar[1]";
////        qWarning() << a << "aaa" << "bbb";
//        qWarning() << ":Lidar[2]" << "aaa" << "bbb";
//    }
    QWidget w;
    w.show();
    return a.exec();
}
