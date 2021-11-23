/*************************************************************************
    > File Name: wrap.h
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov 22 18:16:02 2021
    > Description: 
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<errno.h>

void perr_exit(const char *s);

int Socket(int domain, int type, int protocol);

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int Listen(int sockfd, int backlog);

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

ssize_t Read(int fd, void *buf, size_t count);

ssize_t Write(int fd, const void *buf, size_t count);

int Close(int fd);

/* 读取 n 个字符到 buf，返回读取的字符总数 */
int Readn(int fd, void *buf, int n); 

/* 写 n 个字符到 buf，返回写的字符总数 */
int Writen(int fd, void *buf, int n); 

/* 用于实现 Readline */
//ssize_t my_read(int fd, char *buf, int count);

/* 从 fd 读取一行到buf */
char *Readline(int fd, char *buf);
