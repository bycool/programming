obj-m+=relay_test.o

relayko-obj := relay_test.o

all:ko app

app:
	gcc appread.c -o app

ko:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm app
