shmget(得到一个共享内存标识符或创建一个共享内存对象)
1,所需头文件: #include <sys/ipc.h>
			  #include <sys/shm.h>

2,函数说明:得到一个共享内存标识符或创建一个共享内存对象并返回共享内存标识符

3函数原型:
	int shmget(key_t key, size_t size, int shmflg)

4,参数：
.key:
	0(IPC_PRIVATE)：会建立新共享内存对象
	大于0的32位整数：视参数shmflg来确定操作。通常要求此值来源于ftok返回的IPC键值
.size:
	大于0的整数：新建的共享内存大小，以字节为单位
	0：只获取共享内存时指定为0
.shmflg:
	0：取共享内存标识符，若不存在则函数会报错
	IPC_CREAT：当shmflg&IPC_CREAT为真时，如果内核中不存在键值与key相等的共享内存，则新建一个共享内存；如果存在这样的共享内存，返回此共享内存的标识符
	IPC_CREAT|IPC_EXCL：如果内核中不存在键值 与key相等的共享内存，则新建一个共享内存；如果存在这样的共享内存则报错

5,函数返回值
	成功：返回共享内存的标识符
	出错：-1，错误原因存于error中

附加说明
上述shmflg参数为模式标志参数，使用时需要与IPC对象存取权限（如0600）进行|运算来确定信号量集的存取权限
错误代码
EINVAL：参数size小于SHMMIN或大于SHMMAX
EEXIST：预建立key所指的共享内存，但已经存在
EIDRM：参数key所指的共享内存已经删除
ENOSPC：超过了系统允许建立的共享内存的最大值(SHMALL)
ENOENT：参数key所指的共享内存不存在，而参数shmflg未设IPC_CREAT位
EACCES：没有权限
ENOMEM：核心内存不足
