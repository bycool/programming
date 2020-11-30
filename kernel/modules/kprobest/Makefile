obj-m := jprobe_example.o

#KDIR    := /home/ten/datum/qemu-kernel/linux-2.6.32.12.x86_64
KDIR := /lib/modules/$(shell uname -r)/build
all:
	make -C $(KDIR) M=$(PWD) modules 
clean:
	rm -f  *.o *.mod.o *.mod.c .*.cmd *.symvers  modul* *.ko.unsigned
