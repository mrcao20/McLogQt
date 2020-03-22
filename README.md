# McLogQt
基于QT的日志记录库

# 2020/3/8
需重构以整理配置文件

# logger
日志记录器，本库默认带有一个default的日志记录器，故新指定的logger无需指定default，当然指定了也没事。logger的作用是创建一个新的日志记录器，每一个logger都可以有独自的配置信息，也可以使用公有的配置。logger的使用方法为：使用qInfo等宏时，在后面接着的括号中构建一个QLoggingCategory，即: qInfo(QLoggingCategory("default")) << "text";当然的，QLoggingCategory("default")也可以使用MC_LOGGER("default")代替。同时，default等级的logger不需要特别指定，即: qInfo() << "text"; 最终会默认输出到default中

---

# logger的配置信息

## level
通过指定level来指定具体需要捕获哪些等级的消息(debug模式下默认为debug以上，release模式下默认为warn以上，且只能指定该等级以上)，等级之间用,分割：debug,warn，debug<warn<critical<fatal<info。
可以通过只指定一个等级并在末尾加上-来表示当前等级及以上：debug-。注意，如果不指定任何等级，则表示不捕获：level=
## console
通过指定console来指定哪些等级的消息会被输出到控制台(debug模式下为level指定的全部，release模式下不输出)，具体用法同level。注意：指定的等级必须在level范围之内
## file
可以通过指定file来指定具体输出到哪个文件中，可以只指定某一等级(debug/file=./log.log)，也可以指定全局(file=./log.log)。注意：全局指定文件只会应用到未
指定文件的等级，如果一个等级已经指定了文件，则全局指定对其无效。ex:如果使用了debug/file=./debug.log，则debug等级的消息只会输出到该文件，而使用file=./log.log
只会影响到其他等级
## append
可以通过指定append来指定输出到文件时是否以追加方式输出，可以指定某一等级，也可以指定全局。同file

---

注意，上面logger的配置信息中如果未指定前缀，那么将会应用到所有logger中(前提是这些logger中的该配置未指定，如果logger中的配置单独指定了，那么该logger中已经指定了的配置不会受到全局配置影响)

目前log已增加文件大小上限功能，暂时固定为10M，等读取配置文件重构完成之后修改为从配置文件读取。log的文件名为配置文件中定义的"文件名_数字"，数字从一开始，超过10M后自动将后面数字加一，如果指定为不以拼接模式打开文件，将会清空数字最大的那个文件，如果指定的文件名已经包含了"文件名_数字"，那么log文件将从该数字后面一位开始。

# 2020/3/8
修改日志文件名的指定方式：
- 如果和之前一样，指定的文件名为全路径，如：file=./log/log.log，那么生成的日志文件名将为log_\[年-月-日_时-分-秒\].log
- 如果没有指定后缀，那么将自动添加.log后缀，其他和上面一样
- 如果只指定了文件夹，如：file=./log/，那么最终文件名将为\[loggerName\]_\[年-月-日_时-分-秒\].log
- 如何指定的文件名以.开头，则最终文件名前缀为loggerName，而且后缀为绝对后缀，即如果指定的文件名为default.text.log，则最终后缀为.text.log<br/>
注意：如果指定文件夹，则必须以/结尾，否则会将其认定为文件名前缀

