# McLogQt
基于QT的日志记录库

# 2020-9-11
移动至McIocBoot仓库，后续均在该仓库中维护

# Usage
1. 如下，引入两个头文件，调用两个静态函数即可
~~~
#include "McLogManager.h"
#include "Configurator/McXMLConfigurator.h"

McXMLConfigurator::configure(R"(E:\QtCreator\McLogQt\Test\logqt.xml)");
McLogManager::installQtMessageHandler();
~~~
或
~~~
#include "McLogManager.h"
#include "Configurator/McINIConfigurator.h"

McINIConfigurator::configure(R"(E:\QtCreator\McLogQt\Test\logqt.ini)");
McLogManager::installQtMessageHandler();
~~~
2. 所有功能在Test代码中均有体现，日志配置在Test文件夹下logqt.xml和logqt.ini文件中。
3. 需要注意的是，ini格式的配置文件仅仅为xml的简化版，只提供了部分功能，Test中的示例配置即为ini所支持的所有配置。

# 注意
1. 该库默认开启了IOC支持，该支持依赖于另一个项目McIocBoot中的McIocContainer库，并且如果要使用XML声明的形式则必须开启此支持。可以在pro文件中加入DEFINES += MC_NO_IOC来关闭IOC。

# 2021-8-13
本库已废弃，迁移至McQuickBoot
