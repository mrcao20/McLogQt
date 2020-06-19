#include "McLog/Appender/impl/McFileDeviceAppender.h"

#include <QFileDevice>

MC_INIT(McFileDeviceAppender)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McFileDeviceAppender))
MC_INIT_END

McFileDeviceAppender::McFileDeviceAppender() 
{
}

McFileDeviceAppender::~McFileDeviceAppender() 
{
}

void McFileDeviceAppender::flush() noexcept 
{
    auto fileDevice = device().staticCast<QFileDevice>();
    
    if(fileDevice.isNull()) {
        return;
    }
    
    fileDevice->flush();
    
    tryNextFile();
}

void McFileDeviceAppender::tryNextFile() noexcept 
{
}
