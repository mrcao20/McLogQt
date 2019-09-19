#ifndef _I_MC_OUTPUT_H_
#define _I_MC_OUTPUT_H_

#include <QString>
#include <qlogging.h>

QT_BEGIN_NAMESPACE
class QFile;
QT_END_NAMESPACE

namespace McLog {

class IMcOutput {
public:
	virtual ~IMcOutput() = default;

	// �����Ҫ��������ļ��豸���˺��������setParentת��file������Ȩ�����ں��ʵ�ʱ���ͷ�file
    virtual void addFileDevice(QFile *file, qint64 maxLen = 0) noexcept = 0;
    /*************************************************
     <��������>       addFileDevice
     <��    ��>      �����ļ�·�����Ƿ�ƴ�ӣ���󳤶ȴ����ļ����������ļ����Զ���ĩβ����1��
                    �������ƴ�ӷ�ʽ�����ļ����ҵ��ļ��Ѵ��ڲ����ļ��Ĵ�С����maxLenʱ�������ļ���ĩβ�������Զ���һ���������µ��ļ�
     <����˵��>		filePath �ļ�·��
                    isAppend �Ƿ���ƴ�ӷ�ʽ���ļ�
                    maxLen �ļ�����󳤶�, ��λkb
     <����ֵ>
     <��    ��>		mrcao
     <ʱ    ��>		2019/9/19
    **************************************************/
    virtual void addFileDevice(const QString &filePath, bool isAppend, qint64 maxLen) noexcept = 0;

	// ���
	virtual void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept = 0;
};

}

#endif // !_I_MC_OUTPUT_H_

