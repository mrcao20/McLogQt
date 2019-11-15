#include <QApplication>

#include <qdebug.h>
#include <QWidget>

#include <Property/McPropertyConfigurator.h>
#include <McLogManager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //McLog::McPropertyConfigurator::defaultConfigure();
    McLog::McPropertyConfigurator::configure("/home/twoton/Qtproject/McLogQt/LogQtTest/init.ini");
    McLog::McLogManager::installQtMessageHandler();
    for(int i = 0; i < 10000; ++i){
        QString a = ":Lidar[1]";
        qWarning() << a << "aaa" << "bbb";
        //qWarning() << ":Lidar[2]" << "aaa" << "bbb";
    }
    QWidget w;
    w.show();
    return a.exec();
}
