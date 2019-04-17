#include "McOutput.h"

#include <qfiledevice.h>
#include <qdatetime.h>

#define __DATE_TIME__ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")

namespace McLog {

struct McOutputData {
	QList<QFileDevice *> fileDevices;	// 输出到的文件设备
	QString format;						// 输出的格式
	QString level;						// 输出的等级

	~McOutputData() {
		for (auto device : fileDevices) {
			device->close();
		}
	}
};

McOutput::McOutput(const QString &level, QObject *parent)
	: QObject(parent)
	, d(new McOutputData())
{
	d->level = level.toUpper();
	d->format = "[" + d->level + "]:  "
		+ "Message:%1  File:%2  Line:%3  Function:%4  DateTime:%5\n";
}

McOutput::~McOutput(){
}

void McOutput::addFileDevice(QFileDevice *file) noexcept {
	if (!file)
		return;
	if (d->fileDevices.contains(file))
		return;
	file->setParent(this);
	d->fileDevices << file;
}

void McOutput::output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept {
	// 如果没有定义QT_MESSAGELOGCONTEXT
	if (msgLogCtx.file == Q_NULLPTR
		&& msgLogCtx.line == 0
		&& msgLogCtx.function == Q_NULLPTR) {
		fprintf_s(stderr, "in release, need to manual define QT_MESSAGELOGCONTEXT\n");
	}
	QString str = d->format.arg(msg, msgLogCtx.file,
		QString::number(msgLogCtx.line),
		msgLogCtx.function, __DATE_TIME__);
	for (auto file : d->fileDevices) {
		file->write(str.toLocal8Bit());
		file->flush();
	}

	if (d->level == "FATAL") {
		abort();
	}
}

}