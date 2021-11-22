/*************************************************************************
    > File Name: wrap.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov 22 18:15:22 2021
    > Description: 封装的函数的实现 
 ************************************************************************/

#include"wrap.h"

void perr_exit(const char *s) {
	perror(s);
	exit(1);
}

int Socket(int domain, int type, int protocol) {

}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {

}

int Listen(int sockfd, int backlog) {

}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {

}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {

}

ssize_t Read(int fd, void *buf, size_t count) {

}

ssize_t Write(int fd, const void *buf, size_t count) {

}

int Close(int fd) {

}

