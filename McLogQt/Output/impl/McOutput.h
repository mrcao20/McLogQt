/**
	Ĭ������¼Ȳ����������̨��Ҳ��������ļ�����Ҫ�ֶ�����
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

	// �����Ҫ��������ļ��豸����ͨ��setParent������Ȩת�Ƶ�������
	void addFileDevice(QFileDevice *file) noexcept;

	// ���
	void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept override;

private:
	QScopedPointer<McOutputData> d;
};

}

#endif // !_MC_OUTPUT_H_
