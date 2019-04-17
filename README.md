# McLogQt
基于QT的日志记录库<br/>
如果没有指定任何配置，则会采用默认配置：debug模式下会捕获debug以上所有消息，并输出到控制台，不输出到文件；release模式下捕获warn以上所有消息，不输出到控制台，输出到当前文件夹下的log.log文件里(若此文件存在，则会输出到log1.log，以此类推)

# logger
通过指定logger来指定具体需要捕获哪些等级的消息(debug模式下默认为debug以上，release模式下默认为warn以上，且只能指定该等级以上)，debug<warn<critical<fatal<info。
可以通过只指定一个等级并在末尾加上-来表示当前等级及以上：debug-。注意，如果不指定任何等级，则表示不捕获：logger=
# console
通过指定console来指定哪些等级的消息会被输出到控制台(debug模式下为logger指定的全部，release模式下不输出)，具体用法同logger。注意：指定的等级必须在logger范围之内
# file
可以通过指定file来指定具体输出到哪个文件中，可以只指定某一等级(debug/file=./log.log)，也可以指定全局(file=./log.log)。注意：全局指定文件只会应用到未
指定文件的等级，如果一个等级已经指定了文件，则全局指定对其无效。ex:如果使用了debug/file=./debug.log，则debug等级的消息只会输出到该文件，而使用file=./log.log
只会影响到其他等级
# append
可以通过指定append来指定输出到文件时是否以追加方式输出，可以指定某一等级，也可以指定全局。同file
