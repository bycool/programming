obj-m	:= bb.o
bb-objs	:=	blkmdev.o

#KDIR	:= /home/ten/datum/qemu-kernel/linux-4.10
KDIR	:= /lib/modules/$(shell uname -r)/build
PWD	:= $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm *.o *.mod.* *odule* *.ko .*.cmd *.unsigned .tmp_versions .blkmdev.o.d -rf
