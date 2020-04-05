#pragma once

#include "../IMcLayout.h"

MC_FORWARD_DECL_PRIVATE_DATA(McPatternLayout);

class MCLOGQT_EXPORT McPatternLayout : public QObject, public IMcLayout {
    Q_OBJECT
    MC_DECL_INIT(McPatternLayout)
    MC_DEFINE_TYPELIST(QObject, MC_DECL_TYPELIST(IMcLayout))
    Q_PROPERTY(QString pattern READ getPattern WRITE setPattern)
public:
    Q_INVOKABLE McPatternLayout();
    ~McPatternLayout() override;
    
    QString getPattern() const noexcept;
    void setPattern(const QString &val) noexcept;
    
    QString format(QtMsgType type, const QMessageLogContext &context, const QString &str) noexcept override;
    
private:
    MC_DECL_PRIVATE(McPatternLayout)
};

MC_DECL_METATYPE(McPatternLayout)
