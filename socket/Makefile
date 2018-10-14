LINK=-I./include/ -L../libs/
all:service client 
service:service.o
	gcc service.o -o service $(LINK)
service.o:service.c
	gcc -c service.c -o service.o $(LINK)
client:client.o
	gcc client.o -o client $(LINK)
client.o:client.c
	gcc -c client.c -o client.o $(LINK)
.PHONY:clean
clean:
	rm -rf *.o client service 
