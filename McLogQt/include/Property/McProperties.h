#pragma once

#include <qhash.h>

QT_BEGIN_NAMESPACE
class QSettings;
class QFileDevice;
QT_END_NAMESPACE

namespace McLog {

class IMcOutput;

class McProperties : public QHash<QtMsgType, IMcOutput *> {

public:
	McProperties();
	~McProperties();

    void load(const QString& loggerName, QSettings &settings) noexcept;

private:
	void getValue(QStringList &list, const QSettings &setting, 
        const QString& loggerName, const QString &key, const QString &defaultValue) noexcept;
	// 将传入的类型转换为对应的枚举，如果不存在，则返回-1
	QtMsgType strToEnum(const QString &logger) noexcept;
	void initLevel(QStringList &levels) noexcept;
    void createOutput(const QString& loggerName, const QStringList &loggers) noexcept;
	void setOutputIsConsole(QStringList &consoles, const QStringList &loggers) noexcept;
    void setOutputFile(const QSettings &setting, const QString& loggerName, const QStringList &loggers) noexcept;
    bool isFileAppend(const QSettings &setting, const QString& loggerName, const QString &logger) noexcept;
	bool checkFilePath(const QString &filePath) noexcept;

};

}
