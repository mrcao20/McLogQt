/**
	Ĭ������¼Ȳ����������̨��Ҳ��������ļ�����Ҫ�ֶ�����
*/

#ifndef _MC_OUTPUT_H_
#define _MC_OUTPUT_H_

#include <QObject>
#include "../IMcOutput.h"

#include <QIODevice>

namespace McLog {

struct McOutputData;

class McOutput : public QObject, public IMcOutput {
    Q_OBJECT
    Q_DISABLE_COPY(McOutput)

public:
	explicit McOutput(const QString &level, QObject *parent = 0);
	virtual ~McOutput();

	// �����Ҫ��������ļ��豸����ͨ��setParent������Ȩת�Ƶ�������
    void addFileDevice(QFile *file, qint64 maxLen = 0) noexcept override;
    void addFileDevice(const QString &filePath, bool isAppend, qint64 maxLen) noexcept override;

	// ���
	void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept override;

private:
    QString getNewFilePath(const QString& filePath);
    // ��λbyte
    bool createNewFile(QFile *file, const QString& filePath, QIODevice::OpenMode mode, qint64 maxLen) noexcept;

private:
	QScopedPointer<McOutputData> d;
};

}

#endif // !_MC_OUTPUT_H_
