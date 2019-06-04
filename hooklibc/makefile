KDIR   := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)



test: testfunc.o hook.so
	gcc testfunc.c -o main

hook.so: hookfunc.c
	gcc -fPIC -shared hookfunc.c -o hook.so -ldl

clean:
	rm main 1.txt1 *.o -f
