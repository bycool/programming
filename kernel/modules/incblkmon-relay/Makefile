obj-m	:=	bb.o
bb-objs	:=	incmon.o

#KDIR	:=	/home/ten/datum/qemu-kernel/linux-2.6.32.12.x86_64
KDIR   := /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm *.o *.mod.* *odule* *.ko .*.cmd *.unsigned .tmp_versions .*.o.d -rf
