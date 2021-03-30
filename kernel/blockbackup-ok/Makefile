obj-m	:= bb.o
bb-objs	:= bbdevhandler.o \
		   bbfilter.o \
		   bbrelay.o \
		   bbackup.o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)
EXTRA_CFLAGS	:= -g

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules
	rm *.o *.mod.* *odule* .*.cmd *.unsigned bb.ko.unsigned *.mod.c *.mod.o .tmp_versions -rf
	gcc app.c -o app

clean:
	rm app *.o *.ko *.mod.* *odule* .*.cmd *.unsigned bb.ko.unsigned *.mod.c *.mod.o .tmp_versions -rf
