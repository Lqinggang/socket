/****************************************
   > File Name: client.c
   > Author: lqinggang
   > Email: 1944058861@qq.com
   > Create Time: Tue 04 Dec 2018 09:37:30 AM CST
****************************************/


#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BUFFSIZE 1024

int main(int argc,char *argv[])
{
    //1:sevice address
    struct sockaddr_in serveraddr;
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //service address
    serveraddr.sin_port = htons(12345); //the port of server to listen
    serveraddr.sin_family = AF_INET; //ipv4

    //2:cerate a socket 
    int socketfd;
    if((socketfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
        printf("socket error\n");
        return (errno);
    }

    //3:connect to the server
    if(connect(socketfd,(struct sockaddr *)&serveraddr,sizeof(struct sockaddr)) < 0){
        printf("connect error: %d\n",errno);
        return (errno);
    }

    //4:send message to the server
    char buff[BUFFSIZE];
    printf("%% ");
    while(fgets(buff,BUFFSIZE,stdin) != NULL) { //fgets include '\n'
       printf("message: %s",buff); 
       printf("send types: %ld\n",(long)send(socketfd,&buff,strlen(buff) - 1,0)); //does not include '\n'
        printf("%% ");
    }
    close(socketfd);
    return 0;

}
