obj-m := jprobe_example.o

KDIR := /lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules 
clean:
	rm -f  *.o *.mod.o *.mod.c .*.cmd *.symvers  modul* *.ko.unsigned
