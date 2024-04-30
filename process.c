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

void msgRecv(int s)
{
    ssize_t size = 0;
    char buffer[1024];
    while(1)
    {
        size = recv(s,buffer,1024,0);
        if (!size)
        {
            break;
        }
        printf("you get:%s",buffer);
    }
}

void msgSend(int s)
{
    ssize_t size = 0;
    char buffer[1024];
    while (1)
    {
        size = read(0,buffer,1024);
        if (!size)
        {
            break;
        }
        send(s,buffer,sizeof(buffer)+1,0);
    }
    
}