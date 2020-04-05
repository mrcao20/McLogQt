#pragma once

#include "McFileDeviceAppender.h"

class MCLOGQT_EXPORT McConsoleAppender : public McFileDeviceAppender {
    Q_OBJECT
    MC_DECL_INIT(McConsoleAppender)
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(McFileDeviceAppender))
public:
    Q_INVOKABLE McConsoleAppender();
    ~McConsoleAppender() override;
    
    Q_INVOKABLE
    MC_BEAN_FINISHED
    void finished() noexcept;
};

MC_DECL_METATYPE(McConsoleAppender)
