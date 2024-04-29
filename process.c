#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "process.h"
void process_client(int s)
{
    ssize_t size = 0;
    char buffer[1024];
    char exitword[] = "quit";
    while (1)
    {
        size  = read(0,buffer,1024);
        if (size == 0)
        {
            break;
        }
        send(s,buffer,strlen(buffer)+1,0);
        size = recv(s,buffer,1024,0);
        printf("server:%s",buffer);
        memset(buffer,'\0',1024);
    }
}

void process_server(int s)
{
    ssize_t size = 0;
    char buffer[1024];
    char ack[] = "server recept!";
    while (1)
    {
        size = recv(s,buffer,1024,0);
        printf("server has recv:%s\n",buffer);
        if (size == 0)
        {
            printf("server error!!!\n");
            return ;
        }
        send(s,buffer,strlen(buffer)+1,0);
    }
}