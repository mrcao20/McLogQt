#ifndef _MC_PROPERTY_CONFIGURATOR_H_
#define _MC_PROPERTY_CONFIGURATOR_H_

#include <QObject>
#include <qsettings.h>

#include "mclogqt_global.h"

namespace McLog {

class IMcLoggerRepository;

class MCLOGQT_EXPORT McPropertyConfigurator : public QObject {
	Q_OBJECT

public:
	McPropertyConfigurator(QObject *parent = 0);
	~McPropertyConfigurator();

	static void configure(const QString &configFilename) noexcept;
	static void configure(QSettings &settings) noexcept;

	void doConfigure(QSettings &settings, IMcLoggerRepository *loggerRepository = Q_NULLPTR) noexcept;
};

}

#endif // !_MC_PROPERTY_CONFIGURATOR_H_