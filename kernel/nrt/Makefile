obj-m	:= nn.o
nn-objs	:= nrt.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	gcc userapp.c -o app -pthread
clean:
	rm *.o -rf  
	rm *.mod.* -rf  
	rm *odule* -rf
	rm *.ko -rf
	rm .*.cmd -rf
	rm *.unsigned -rf
	rm .tmp_versions -rf

