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

	// 添加需要输出到的文件设备，此函数会调用setParent转移file的所有权，并在合适的时候释放file
    virtual void addFileDevice(QFile *file, qint64 maxLen = 0) noexcept = 0;
    /*************************************************
     <函数名称>       addFileDevice
     <功    能>      根据文件路径，是否拼接，最大长度创建文件，创建的文件会自动在末尾补上1，
                    如果是以拼接方式创建文件并且当文件已存在并且文件的大小大于maxLen时，会让文件名末尾的数字自动加一，并创建新的文件
     <参数说明>		filePath 文件路径
                    isAppend 是否以拼接方式打开文件
                    maxLen 文件的最大长度, 单位kb
     <返回值>
     <作    者>		mrcao
     <时    间>		2019/9/19
    **************************************************/
    virtual void addFileDevice(const QString &filePath, bool isAppend, qint64 maxLen) noexcept = 0;

	// 输出
	virtual void output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept = 0;
};

}

#endif // !_I_MC_OUTPUT_H_

