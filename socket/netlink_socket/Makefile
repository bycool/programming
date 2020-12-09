obj-m += ker.o
 
 
KID := /lib/modules/`uname -r`/build
PWD := $(shell pwd)
 
all:
	make -C $(KID) M=$(PWD) modules
	gcc app.c -o app
clean:
	rm -rf *.o .cmd *.ko *.mod.c .tmp_versions modules.order  Module.symvers *.unsigned app .k*

