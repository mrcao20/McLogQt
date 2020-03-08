#pragma once

#include <QObject>
#include <qsettings.h>

#include "..//McLogQt_Global.h"

namespace McLog {

class IMcLoggerRepository;

class MCLOGQT_EXPORT McPropertyConfigurator : public QObject {
	Q_OBJECT

public:
	McPropertyConfigurator(QObject *parent = nullptr);
	~McPropertyConfigurator();

	static void defaultConfigure() noexcept;
	static void configure(const QString &configFilename) noexcept;
	static void configure(QSettings &settings) noexcept;

	void doConfigure(QSettings &settings, IMcLoggerRepository *loggerRepository = Q_NULLPTR) noexcept;
};

}
