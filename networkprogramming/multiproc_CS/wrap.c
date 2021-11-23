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
	int fd;
	fd = socket(domain, type, protocol);
	if(fd == -1) {
		perr_exit("socket error");
	}
	return fd;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	int ret;
	ret = bind(sockfd, addr, addrlen);
	if(ret == -1) {
		perr_exit("bind error");
	}
	return ret;
}

int Listen(int sockfd, int backlog) {
	int ret;
	ret = listen(sockfd, backlog);
	if(ret == -1) {
		perr_exit("listen error");
	}
	return ret;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
	int fd;

again:
	if(fd = accept(sockfd, addr, addrlen) == -1) {
		if(errno == ECONNABORTED || errno == EINTR)
			goto again;
		else
			perr_exit("accept error");
	}

	return fd;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
	int ret;
	ret = connect(sockfd, addr, addrlen);
	if(ret == -1) {
		perr_exit("connect error");
	}

	return ret;	
}

ssize_t Read(int fd, void *buf, size_t count) {
	ssize_t ret;

again:
	if((ret = read(fd, buf, count)) == -1) {
		if(errno == EINTR)
			goto again;
		else
			perr_exit("read error");
	}

	return ret;
}

ssize_t Write(int fd, const void *buf, size_t count) {
	ssize_t ret;

again:
	if((ret = write(fd, buf, count)) == -1) {
		if(errno == EINTR)
			goto again;
		else
			perr_exit("write error");
	}

	return ret;
}

int Close(int fd) {
	int ret;
	ret = close(fd);
	if(ret == -1) {
		perr_exit("close error");
	}
	return ret;
}

int Readn(int fd, void *buf, int n) {
	int nleft = n; //还未读的字符个数 
	int nread;
	char *p = (char*)buf;

	while(nleft > 0) {
		nread = Read(fd, buf, n);
		nleft -= nread;
		p += nread;
	}

	return n - nleft;
}


int Writen(int fd, void *buf, int n) {
	int nleft = n; //还未写的字符个数 
	int nwritten;
	char *p = (char*)buf;

	while(nleft > 0) {
		nwritten = Write(fd, buf, n);
		nleft -= nwritten;
		p += nwritten;
	}

	return n - nleft;
}

char *Readline(int fd, char *buf) {
	char *p = buf;
	char buffer[100]; //每次读100字节

	while(1) {
		int count = Read(fd, (void*)buffer, sizeof(buffer));
		int i = 0;

		/* 朱字符遍历读到的字符，查看是否换行或到末尾 */
		for(; i < count; i++) {
			char c = *(buffer + i);
			*p = c;
			p++;
			if(c == '\n' || c == '\0'){ //一行或结束
				return buf;
			}
		}
	}
	return buf;
}
