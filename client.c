#include <stdio.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include "process.h"
#define POST 8888
int main()
{
    int sc,err;
    struct sockaddr_in server_addr;
    char addr[] = "192.168.1.7";
    sc = socket(AF_INET,SOCK_STREAM,0);
    if(sc < 0)
    {
        printf("socket erorr!!\n");
        return -1;
    }
        
    bzero(&server_addr , sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(addr);
    server_addr.sin_port = htons(POST);

    connect(sc,(struct sockaddr*)&server_addr,sizeof(struct sockaddr));
    printf("server has connect!\n");
    //process_client(sc);
    ssize_t size = 0;
    char buffer[1024];
    char exitword[] = "quit";
    while (1)
    {
        printf("waiting \n");  
        send(sc,exitword,strlen(exitword) + 1,0);
        printf("client send!\n");
        size = recv(sc,buffer,1024,0);
        printf("server say:%s",buffer);
        sleep(4);
    }

    close(sc);
    return 0;
}