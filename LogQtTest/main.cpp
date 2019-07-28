#include <QtCore/QCoreApplication>

#include <qdebug.h>

#include <Property/McPropertyConfigurator.h>
#include <McLogManager.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    McLog::McPropertyConfigurator::defaultConfigure();
    McLog::McLogManager::installQtMessageHandler();
    qWarning() << "aaa";
    return a.exec();
}
