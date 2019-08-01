#include <QtCore/QCoreApplication>

#include <qdebug.h>

#include <Property/McPropertyConfigurator.h>
#include <McLogManager.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    McLog::McPropertyConfigurator::defaultConfigure();
    //McLog::McPropertyConfigurator::configure("/home/twoton/Qtproject/McLogQt/LogQtTest/init.ini");
    McLog::McLogManager::installQtMessageHandler();
    qWarning() << ":lidar[1]" << "aaa" << "bbb";
    return a.exec();
}
