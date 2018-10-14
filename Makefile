all:service client
service:service.o
	gcc service.o -o service
service.o:service.c
	gcc -c service.c -o service.o
client:client.o
	gcc client.o -o client
client.o:client.c
	gcc -c client.c -o client.o
.PHONY:clean
clean:
	rm -rf client client.o service service.o
