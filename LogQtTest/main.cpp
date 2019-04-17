#include <QtCore/QCoreApplication>

#include <qdebug.h>

#include <../McLogQt/McPropertyConfigurator.h>
#include <../McLogQt/McLogManager.h>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	McLog::McPropertyConfigurator::configure("./init.ini");
	McLog::McLogManager::installQtMessageHandler();
	qInfo() << "aaa";
	return a.exec();
}
