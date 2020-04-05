SOURCES += \
    $$PWD/src/Appender/McAbstractAppender.cpp \
    $$PWD/src/Appender/McConsoleAppender.cpp \
    $$PWD/src/Appender/McDailyRollingFileAppender.cpp \
    $$PWD/src/Appender/McFileAppender.cpp \
    $$PWD/src/Appender/McFileDeviceAppender.cpp \
    $$PWD/src/Appender/McRollingFileAppender.cpp \
    $$PWD/src/Appender/McSizeRollingFileAppender.cpp \
    $$PWD/src/Configurator/McXMLConfigurator.cpp \
    $$PWD/src/Layout/McNormalLayout.cpp \
    $$PWD/src/Layout/McPatternLayout.cpp \
    $$PWD/src/Layout/McSimpleLayout.cpp \
    $$PWD/src/Layout/McTTCCLayout.cpp \
    $$PWD/src/Logger/McLogger.cpp \
    $$PWD/src/McLogManager.cpp \
    $$PWD/src/Repository/McLoggerRepository.cpp

HEADERS += \
        $$PWD/include/Appender/IMcAppender.h \
        $$PWD/include/Appender/IMcConfigurableAppender.h \
        $$PWD/include/Appender/IMcWritableAppender.h \
        $$PWD/include/Appender/impl/McAbstractAppender.h \
        $$PWD/include/Appender/impl/McConsoleAppender.h \
        $$PWD/include/Appender/impl/McDailyRollingFileAppender.h \
        $$PWD/include/Appender/impl/McFileAppender.h \
        $$PWD/include/Appender/impl/McFileDeviceAppender.h \
        $$PWD/include/Appender/impl/McRollingFileAppender.h \
        $$PWD/include/Appender/impl/McSizeRollingFileAppender.h \
        $$PWD/include/Configurator/McXMLConfigurator.h \
        $$PWD/include/Layout/IMcLayout.h \
        $$PWD/include/Layout/impl/McNormalLayout.h \
        $$PWD/include/Layout/impl/McPatternLayout.h \
        $$PWD/include/Layout/impl/McSimpleLayout.h \
        $$PWD/include/Layout/impl/McTTCCLayout.h \
        $$PWD/include/Logger/IMcLogger.h \
        $$PWD/include/Logger/impl/McLogger.h \
        $$PWD/include/McLogGlobal.h \
        $$PWD/include/McLogMacroGlobal.h \
        $$PWD/include/McLogManager.h \
        $$PWD/include/McLogVersion.h \
        $$PWD/include/Repository/IMcLoggerRepository.h \
        $$PWD/include/Repository/impl/McLoggerRepository.h