obj-m	:= cs.o
cs-objs	:= callsys.o

KDIR	:= /lib/modules/$(shell uname -r)/build
PWD		:= $(shell pwd)
INCL	:= -I.

all:
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm *.o -rf  
	rm *.mod.* -rf  
	rm *odule* -rf
	rm *.ko -rf
	rm .*.cmd -rf
	rm *.unsigned -rf
	rm .tmp_versions -rf

