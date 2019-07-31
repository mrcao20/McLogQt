# McLogQt
基于QT的日志记录库

# logger
日志记录器，本库默认带有一个root的日志记录器，故新指定的logger无需指定root，当然指定了也没事。logger的作用是创建一个新的日志记录器，每一个logger都可以有独自的配置信息，也可以使用公有的配置。logger的使用方法为：当记录日志时，第一个输出字符串使用:[logger]的方式指定对应的logger。即，当我需要记录一个info类型的日志信息"hello world"，需要指定到自定义的一个logger "test"，所使用的格式为：qInfo() << ":test" << "hello world";":test"也可以不指定，当不指定时hello world将会输出到root的logger中。注意，:test中的test必须在配置文件中指定，即该logger必须创建，如果没有创建，那么:test将会作为一个字符串输出到root中。

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
