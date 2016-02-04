/*===============================================================
*   文件名称：server.c
*   创建日期：2016年02月02日
================================================================*/
//#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define DEFAULT_PORT 8000
#define MAXLINE 4096

int main(int argc, char **argv)
{
    int socket_fd, connect_fd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;

    //初始化socket
    if(-1 == (socket_fd = socket(AF_INET, SOCK_STREAM, 0)))
    {
        printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    //初始化
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //IP地址设置，让系统自动获取本机IP
    servaddr.sin_port = htons(DEFAULT_PORT);

    //将本地地址绑定到创建的套接字上
    if(-1 == bind(socket_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    {
        printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    //开始坚挺是否有客户端连接
    if(-1 == listen(socket_fd, 10))
    {
        printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
        exit(0);
    }

    printf("============waiting for client's request=============\n");

    while(1)
    {
        //阻塞知道有客户端连接，不然浪费CPU资源
        if(-1 == (connect_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL)))
        {
            printf("accept socket error: %s(errno: %d)\n", strerror(errno), errno);
        }

        continue;

        //接受客户端传过来的数据
        n = recv(connect_fd, buff, MAXLINE, 0);

        //向客户端发送回应数据
        if(!fork())
        {
            if(-1 == send(connect_fd, "hello, you are connected!\n", 27, 0))
            {
                perror("send error");
                close(connect_fd);
                exit(0);
            }
        }

        buff[n] = '\0';
        printf("recv msg from client: %s\n", buff);
        close(connect_fd);
    }

    close(socket_fd);

    return 0;
}
