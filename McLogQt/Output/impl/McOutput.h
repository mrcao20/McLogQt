/**
	默认情况下既不输出到控制台，也不输出到文件，需要手动设置
*/

#ifndef _MC_OUTPUT_H_
#define _MC_OUTPUT_H_

#include <QObject>
#include "../IMcOutput.h"

namespace McLog {

struct McOutputData;

class McOutput : public QObject, public IMcOutput {
    Q_OBJECT
    Q_DISABLE_COPY(McOutput)

public:
	explicit McOutput(const QString &level, QObject *parent = 0);
	virtual ~McOutput();

	// 添加需要输出到的文件设备，会通过setParent将所有权转移到本对象
	void addFileDevice(QFileDevice *file) noexcept;

	// 输出
	void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept override;

private:
	QScopedPointer<McOutputData> d;
};

}

#endif // !_MC_OUTPUT_H_
