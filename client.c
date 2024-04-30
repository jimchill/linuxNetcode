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
    pthread_t send_id,recv_id;
    int *rval;
    int ret;
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
   // process_client(sc);
    ret = pthread_create(&recv_id,NULL,msgRecv,sc);
    if (ret)
    {
        printf("msgRecv() thread error\n");
    }
    pthread_detach(recv_id);
    ret = pthread_create(&send_id,NULL,msgSend,sc);
    if (ret)
    {
        printf("msgSend() thread error\n");
    }

    
    pthread_detach(send_id);
    pthread_exit(rval);
    close(sc);
    return 0;
}