obj-m := client.o service.o
client-objs := client.o ksocket.o
service-objs := service.o ksocket.o

KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf user *ko *ko.unsigned *.mod.* .*.cmd *.o *.symvers *.order *.markers *.*~ *~ .tmp_versions *.S *.sdtinfo.c
