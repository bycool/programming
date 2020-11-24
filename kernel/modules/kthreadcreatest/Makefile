obj-m	:= tt.o
tt-objs	:= kthreadcreatest.o

KDIR    := /lib/modules/$(shell uname -r)/build
PWD     := $(shell pwd)

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm *.o *.mod.* *odule* *.ko .*.cmd *.unsigned .tmp_versions -rf
