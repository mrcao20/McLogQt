#include "McPropertyConfigurator.h"

#include <qdebug.h>

#include "McLogManager.h"
#include "McProperties.h"
#include "IMcLoggerRepository.h"

namespace McLog {

McPropertyConfigurator::McPropertyConfigurator(QObject *parent)
	: QObject(parent)
{
}

McPropertyConfigurator::~McPropertyConfigurator(){
}

void McPropertyConfigurator::defaultConfigure() noexcept {
	fprintf_s(stderr, "Note: in debug, just output to console; "
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
	McProperties properties;

	properties.load(settings);

	loggerRepository->configureLogger(properties);
}

}