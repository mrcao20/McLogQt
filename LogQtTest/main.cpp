#include <QApplication>

#include <qdebug.h>
#include <QWidget>

#include <Property/McPropertyConfigurator.h>
#include <McLogManager.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //McLog::McPropertyConfigurator::defaultConfigure();
    McLog::McPropertyConfigurator::configure("/home/twoton/Qtproject/McLogQt/build/build-McLogQt-Qt5_8_0_static-Release/LogQtTest/logInit.ini");
    McLog::McLogManager::installQtMessageHandler();
    for(int i = 0; i < 10000; ++i){
        qWarning() << ":lidar[1]" << "aaa" << "bbb";
    }
    QWidget w;
    w.show();
    return a.exec();
}
