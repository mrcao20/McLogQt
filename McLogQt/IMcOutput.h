#ifndef _I_MC_OUTPUT_H_
#define _I_MC_OUTPUT_H_

QT_BEGIN_NAMESPACE
class QFileDevice;
QT_END_NAMESPACE

namespace McLog {

class IMcOutput {
public:
	virtual ~IMcOutput() = default;

	// �����Ҫ��������ļ��豸���˺��������setParentת��file������Ȩ�����ں��ʵ�ʱ���ͷ�file
	virtual void addFileDevice(QFileDevice *file) noexcept = 0;

	// ���
	virtual void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept = 0;
};

}

#endif // !_I_MC_OUTPUT_H_

