#pragma once

namespace McLog {

class McProperties;

class IMcLogger {
public:
    virtual ~IMcLogger() = default;
    
    virtual void setProperties(const McProperties &properties) noexcept = 0;
};

}
