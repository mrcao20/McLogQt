#pragma once

#include "McPatternLayout.h"

class MCLOGQT_EXPORT McTTCCLayout : public McPatternLayout {
    Q_OBJECT
    MC_DECL_INIT(McTTCCLayout)
    MC_DEFINE_TYPELIST(MC_DECL_TYPELIST(McPatternLayout))
public:
    Q_INVOKABLE McTTCCLayout(){}
    
    Q_INVOKABLE
    MC_BEAN_FINISHED
    void finished() noexcept;
};

MC_DECL_METATYPE(McTTCCLayout)
