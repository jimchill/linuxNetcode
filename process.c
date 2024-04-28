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
        // if (!strcmp(buffer,exitword))
        // {
        //     break;
        // }
        
        size = read(0,exitword,1024);
        printf("read done\n");
        if (size > 0)
        {
            send(s,exitword,size,0);
            printf("client send!\n");
            size = recv(s,buffer,1024,0);
        }
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
        if (size == 0)
        {
            return ;
        }

        sprintf(buffer,"%d bytes altogether\n",size);
        send(s,ack,strlen(ack)+1,0);
    }
}