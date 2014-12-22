season5 filestream
一，流和定向：
	对于文件IO来说，所有IO函数都是针对文件描述符展开的。对于标准IO而言，所有函数都是针对流展开的。管理的结构体是FILE。
	FILE结构体通常包括：
		文件fd
		缓存区指针
		缓存区长度
		当前缓冲区读写长度
		出错标志

	流的定向(stream's orientation)决定了所读写的字符是单字节还是多字节的。一个流最初创建的时候没有定向，直到第一次使用才被确定。有两个函数可以修改流的定向：
	freopen 这个函数清除了流的定向
	fwide(FILE* fp, int mode).这个函数修改流的定向.


二，缓冲：
	标准IO相对于文件IO最便利的地方就是提供了缓冲。缓冲的话大部分情况能够改善程序的性能。
	标准IO提供了三种缓冲：
		全缓冲
		行缓冲
		不带缓冲
	全缓冲：指填满IO缓冲区之后在进行实际的IO操作，通常来说对于驻留在磁盘上的文件使用全缓冲。在流上第一次实行IO操作的时候，标准IO就会通过malloc分配一块缓冲区。如果使用全缓冲需要强制进行实际操作的话，可以用fflush来冲刷。对于fflush有两层意思，对于标准IO而言，flush是将缓冲区的内容进行实际IO操作，而对于设备驱动程序而言，就是丢弃缓冲区里面的内容。
	行缓冲：指输入和输出遇到换行符之后，标准IO库才执行IO操作。当然如果缓冲区已满的话，那么也是会进行IO操作的。并且任何时候如果标准IO库重一个不带缓冲的流，或者从内核得到数据的带缓冲流中获得数据的话，会造成冲洗所有行缓冲输出流。通常来说对于终端设备比如标准输入和输出的时候会使用行缓冲。
	不带缓冲：指不对字符进行任何缓冲。通常对于标准错误来说，希望信息尽可能快地显示出来，所以不带缓冲。

	对于Linux平台来说：
		标准错误是不带缓冲的
		终端设备是行缓冲
		其他都是全缓冲的

	提供API来设置缓冲模式：
	//打开和关闭缓冲模式
	//如果buf！=NULL，buf必须是BUFSIZE大小缓冲区，那么选择合适的缓冲模式
	//如果buf ==NULL，那么表示不带缓冲
	void setbuf(FILE* restrict fp, char* restrict buf);

	//mode可以执行什么缓冲模式
	//如果不带缓冲，那么忽略buf和size
	//如果带缓冲，那么使用buf和size，如果buf==NULL，那么size=BUFSIZE
	int setvbuf(FILE* restrict fp, char* restrict buf, int mode, size_t size);

	如果fflush传入参数为NULL的话，那么会刷出所有的输出流。如果程序退出之前没有关闭流的话，标注IO会自动帮助我们关闭。


三，打开和关闭流
	打开流提供了下面这些函数
//打开pathname的文件
FILE* fopen(const char* restrict pathname, const char* restrict type)
//关闭fp，然后打开pathname，和fp进行关联
FILE* freopen(const cahr* restrict pathname, const char* restrict type, FILE* restrict fp)
//将打开的fd映射成流
FILE* fdopen(int fd, const char* type);

	通常来说freopen的用途是，将fp设置成为stdin,stdout，或者是stderr，这样原来操作fprintf函数的话，就可以直接关联到文件上面了。
	type			说明
	r/rb			读打开
	w/wb			截断写打开，如果不存在创建
	a/ab			追加写打开，如果不存在创建
	r+/r+b/rb+		读写打开
	w+/w+b/wb+		截断读写打开，如果不存在创建
	a+/a+b/ab+		追加读写打开，如果不存在创建
	使用字符b作为type的一部分，这使得标准IO系统可以区分文本文件和二进制文件。因为unix内核并不对这两种文件进行区分，所以在UNIX系统环境下制定字符b作为type的一部分实际上并无作用。

	当以读和写类型打开一文件时(type中+符号)，具有下列限制：
	.如果中间没有fflush、fseek、fsetpos或者rewind，则在输出的后面不能直接跟随输入。
	.如果中间没有fseek、fsetpos或rewind，或者一个输入操作没有到达文件尾端，则在输入操作之后不能直接跟随输出。

#include <stdio.h>
int fclose(FILE *fp) 
:文件关闭前，冲洗缓冲区中的输出数据。丢弃缓冲区中的任何输入数据。如果标准IO库已经为该流自动分配一个缓冲区，则释放此缓冲区。
:当一个进程正常终止时(exit函数，从main函数返回)，则所有带未写缓冲数据的标准IO流都会被冲洗，所以打开标准IO流都会被关闭。

四，读和写流
	一旦打开流，则可在三种不同类型的非格式化的IO中进行选择，对其进行读、写操作：
	1。每次一个字符的IO，一次读写一个字符，如果带缓冲的，则标准IO函数会处理所有缓冲。
	2。每次一行的IO，如果想要一次读或写一样，则使用fgets和fputs。每行都以一个换行符终止。
	3。直接IO。fread和fwrite函数支持这种类型的IO。每次IO操作读或写某种数量的对象，而每个对象具有指定的长度。这两个函数通常用于从二进制文件中每次读写一个结构。
 1输入函数：
	以下三个函数可用于一次读一个字符。
	#include <stdio.h>
	int getc(FILE* fp)
	int fgetc(FILE* fp)
	int getchar(void);
	三个函数的返回值：成功返回下一个字符，若已经达到文件结尾或出错则返回EOF


























