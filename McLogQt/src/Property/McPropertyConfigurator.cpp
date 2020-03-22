#include "include/Property/McPropertyConfigurator.h"

#include <qglobal.h>
#include <qdebug.h>

#include "include/McLogManager.h"
#include "include/Property/McProperties.h"
#include "include/Repository/IMcLoggerRepository.h"
#include "include/Logger/impl/McLogger.h"

namespace McLog {

McPropertyConfigurator::McPropertyConfigurator(QObject *parent)
	: QObject(parent)
{
}

McPropertyConfigurator::~McPropertyConfigurator(){
}

void McPropertyConfigurator::defaultConfigure() noexcept {
    fprintf(stderr, "Note: in debug, just output to console; "
		"in release, not output!!\n");
	configure("");
}

void McPropertyConfigurator::configure(const QString &configFilename) noexcept {
	QSettings settings(configFilename, QSettings::IniFormat);
	configure(settings);
}

void McPropertyConfigurator::configure(QSettings &settings) noexcept {
	McPropertyConfigurator configurator;
	configurator.doConfigure(settings);
}

void McPropertyConfigurator::doConfigure(QSettings &settings, IMcLoggerRepository *loggerRepository) noexcept {
	if (!loggerRepository)
		loggerRepository = McLogManager::getInstance()->getLoggerRepository();

#ifdef QT_DEBUG
    QString section = "DEBUG";
#else
    QString section = "RELEASE";
#endif // QT_DEBUG

    settings.beginGroup(section);

    QStringList loggerNames = settings.value("logger").toStringList();
    if(!loggerNames.contains(DEFAULT_LOGGER))
        loggerNames.prepend(DEFAULT_LOGGER);

    for(auto& loggerName : loggerNames){
        McProperties properties;

        properties.load(loggerName, settings);

        IMcLogger *logger = new McLogger();
        logger->setProperties(properties);
        loggerRepository->addLogger(loggerName, logger);
    }

    settings.endGroup();
}

}
