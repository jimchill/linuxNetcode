#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include "process.h"
#define POST 8888
#define BACKLOG 3
#define MAX 10
int main()
{
    int ss,sc;
    int err;
    char addr_server[] = "192.168.1.7";
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    pthread_t client_id[MAX];
    int index = 0;
    int ret;
    int *rval;
    ss = socket(AF_INET,SOCK_STREAM,0);
    if (ss < 0)
    {
        printf("socket error\n");
		return -1;	
    }

    bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(addr_server);
    server_addr.sin_port = htons(POST);

    err = bind(ss,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if (err < 0)
    {
        printf("bind error\n");
		return -1;
    }
    
    err = listen(ss,BACKLOG);
    if (err < 0)
    {
        printf("listen error\n");
		return -1;
    }

    printf("listenning...\n");
    while (1)
    {
        socklen_t addrlen = sizeof(struct sockaddr);

        sc = accept(ss , (struct sockaddr*)&client_addr,&addrlen);

        if (sc < 0)
        {
            printf("client connect error!!\n");
            continue;
        }
        printf("%d:client has connect!!!\n",sc);

        //process_server(sc);
        if (index < MAX)
        {
            ret = pthread_create(&client_id[index],NULL,msgRecv,sc);
            index++;
        }        
        if (ret)
        {
            printf("msgRecv() thread error\n");
        }
        pthread_detach(client_id[index]);

        if (index < MAX)
        {
            int ret = pthread_create(&client_id[index],NULL,msgSend,sc);
            index++;
        }
        
        if (ret)
        {
            printf("msgSend() thread error\n");
        }
        pthread_detach(client_id[index]);
    }
    pthread_exit(rval);
    close(sc);
    return 0;
}