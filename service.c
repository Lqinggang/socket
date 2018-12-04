/****************************************
   > File Name: service.c
   > Author: lqinggang
   > Email: 1944058861@qq.com
   > Create Time: Mon 03 Dec 2018 07:07:47 PM CST
****************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
/*
 * stdio.h : printf,
 * sys/socket.h: socket
 * errno.h: errno
 * arpa/inet.h: sockaddr_in
 */

#define BUFFSIZE 1024



int main(int argc,char *argv[])
{
    //1: create a socket 
    int socketfd;
    if((socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0) { //create socket
        printf("create socket error: %d\n",errno);
        return (errno);
    }

    //2:defined the address to be listen
    struct sockaddr_in addr; //addr 
    addr.sin_addr.s_addr = INADDR_ANY; //any ip to listen
    addr.sin_family = AF_INET; //ipv4
    addr.sin_port = htons(12345);//port

    //3:bind the addres to socket 
    bind(socketfd, (struct sockaddr *)&addr, sizeof(struct sockaddr)); //bind the address to socket

    //4:listen the socket
    if(listen(socketfd,16) < 0) { //add a listener on socket ?
        printf("error on listen: %d\n",errno);
        return (errno);
    }

    //5:accept connection and recevie information from the client
    int acceptfd;
    struct sockaddr_in cliaddr;
    socklen_t addrlen = sizeof(cliaddr);
    while(1) {
       if((acceptfd = accept(socketfd,(struct sockaddr *)&cliaddr,&addrlen)) < 0) {
            printf("accept error: %d\n",errno);
            return (errno);
       } else { //accept
            pid_t pid;
            if((pid = fork()) < 0) { 
                printf("fork error");
                return (errno);
            } else if(pid == 0){ //child  for recevice  information from the client
                struct sockaddr_in clientaddr;
                socklen_t clientaddrlen;
                if(getpeername(acceptfd,(struct sockaddr *)&clientaddr,&clientaddrlen) < 0) {
                    printf("getpeername error.\n");
                } else {
                    printf("conect by %s:%d\n",inet_ntoa(clientaddr.sin_addr),clientaddr.sin_port );
                }
                //6: receive information
                char buff[BUFFSIZE]; //receive buff
                bzero(buff,BUFFSIZE);
                int recv_num; //number of receive from the client
                while((recv_num = recv(acceptfd,&buff,BUFFSIZE,0)) > 0) { 
                   printf("receive msg: %s\n",buff); 
               //    bzero(buff,BUFFSIZE);
                }
                if(errno != EINTR) { //disconnection by client.
                    printf("disconnection.\n");
                    close(acceptfd);
                    exit(0);
                }

            }

       }
    
    }
   return 0;  
}
