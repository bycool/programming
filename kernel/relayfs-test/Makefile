obj-m+=relay.o

relayko-obj := relay.o

all:ko app

app:
	gcc appread.c -o app

ko:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm app
