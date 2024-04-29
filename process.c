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
        printf("waiting \n");  
        send(s,exitword,strlen(exitword) + 1,0);
        printf("client send!\n");
        size = recv(s,buffer,1024,0);
        printf("server say:%s",buffer);
        sleep(4);
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
        printf("server has recv:%s!!\n",buffer);
        if (size == 0)
        {
            printf("server error!!!\n");
            return ;
        }
    
        sprintf(buffer,"%d bytes altogether\n",size);
        send(s,buffer,strlen(buffer)+1,0);
    }
}