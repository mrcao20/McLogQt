/**
	默认情况下既不输出到控制台，也不输出到文件，需要手动设置
*/

#pragma once

#include <QObject>
#include "../IMcOutput.h"

#include <QIODevice>

namespace McLog {

struct McOutputData;

class McOutput : public QObject, public IMcOutput {
    Q_OBJECT
    Q_DISABLE_COPY(McOutput)

public:
    explicit McOutput(const QString& loggerName, const QString &level, QObject *parent = nullptr);
	virtual ~McOutput() override;

	// 添加需要输出到的文件设备，会通过setParent将所有权转移到本对象
    void addFileDevice(QFile *file, qint64 maxLen = 0) noexcept override;
    void addFileDevice(const QString &filePath, bool isAppend, qint64 maxLen) noexcept override;

	// 输出
	void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept override;

private:
    QString getNewFilePath();
    // 单位byte
    void createNewFile(QFile *file, QIODevice::OpenMode mode) noexcept;
    void openFile(QFile *file, const QString &filePath, QIODevice::OpenMode mode);

private:
	QScopedPointer<McOutputData> d;
};

}
