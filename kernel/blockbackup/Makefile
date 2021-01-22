obj-m	:= bb.o
bb-objs	:= 

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	rm *.o *.mod.* *odule* .*.cmd *.unsigned bb.ko.unsigned *.mod.c *.mod.o .tmp_versions -rf

clean:
	rm *.o *.ko *.mod.* *odule* .*.cmd *.unsigned bb.ko.unsigned *.mod.c *.mod.o .tmp_versions -rf
