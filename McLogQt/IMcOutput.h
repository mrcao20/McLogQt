#ifndef _I_MC_OUTPUT_H_
#define _I_MC_OUTPUT_H_

QT_BEGIN_NAMESPACE
class QFileDevice;
QT_END_NAMESPACE

namespace McLog {

class IMcOutput {
public:
	virtual ~IMcOutput() = default;

	// 添加需要输出到的文件设备，此函数会调用setParent转移file的所有权，并在合适的时候释放file
	virtual void addFileDevice(QFileDevice *file) noexcept = 0;

	// 输出
	virtual void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept = 0;
};

}

#endif // !_I_MC_OUTPUT_H_

