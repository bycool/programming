obj-m	:= sydr.o

sydr-objs	:= sync_hook.o \
			   sync_operate.o \
			   relay.o  \
               sync.o	\
               sync_wp.o	\
               sync_utils.o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)
INCL	:= -I .

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	make clean

clean:  
	rm *.o -rf  
	rm *.mod.* -rf  
	rm *odule* -rf
#	rm *.ko -rf
	rm .*.cmd -rf
	rm *.unsigned -rf
	rm .tmp_versions -rf
