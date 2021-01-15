obj-m	:= bi.o
bi-objs	:= blockinfo.o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	rm *.o *.mod.* *odule* .*.cmd *.unsigned .tmp_versions .*.o.d -rf

clean:
	rm *.o *.mod.* *odule* *.ko .*.cmd *.unsigned .tmp_versions .*.o.d -rf
