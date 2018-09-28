all:
	gcc service.c aes128.c -o service -pthread
	gcc client.c aes128.c -o client

clean:
	rm client service
