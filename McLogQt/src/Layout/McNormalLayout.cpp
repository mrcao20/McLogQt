#include "include/Layout/impl/McNormalLayout.h"

MC_INIT(McNormalLayout)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McNormalLayout))
MC_INIT_END

void McNormalLayout::finished() noexcept {
    QString pattern = "[%{time yyyy-MM-dd hh:mm:ss,zzz}][%{category}][%{type}]: "
                      "%{message}  [File:%{file}] [Line:%{line}] [Function:%{function}]";
    setPattern(pattern);
}
