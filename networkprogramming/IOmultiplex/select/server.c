/*************************************************************************
    > File Name: server.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 25 15:16:20 2021
    > Description: 利用select函数实现 IO复用 
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>

#include"wrap.h"

#define BUFSIZE 1024

int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf("Usage: <port>\n");
		exit(1);
	}

	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	fd_set read_set, all_set;
	int maxfd, i, num, strlen;              //maxfd 是最大的文件描述符
	struct timeval timeout;
	char buf[BUFSIZE];

	serv_sock = Socket(AF_INET, SOCK_STREAM	, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	Bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	Listen(serv_sock, 10);

	FD_ZERO(&all_set);
	FD_SET(serv_sock, &all_set);
	maxfd = serv_sock;

	while(1) {
		read_set = all_set;
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		num = select(maxfd + 1, &read_set, NULL, NULL, &timeout);
		if(num == -1) {
			printf("select error");
			exit(1);
		} else if(num == 0) {
			printf("timeout\n");
			continue;
		} else {
			for(i = 0; i <= maxfd; i++) {
				if(FD_ISSET(i, &read_set)) {
					if(i == serv_sock) {
						memset(&clnt_addr, 0, sizeof(clnt_addr));
						clnt_addr_size = sizeof(clnt_addr);
						clnt_sock = Accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
						char clnt_ip[32];
						printf("IP:%s, port:%d\n",
								inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_ip, sizeof(clnt_ip)),
								ntohs(clnt_addr.sin_port));

						FD_SET(clnt_sock, &all_set);
						maxfd = maxfd > clnt_sock ? maxfd : clnt_sock;
					} else {
						strlen = Read(i, buf, sizeof(buf));
						if(strlen == 0) {
							Close(i);
							FD_CLR(i, &all_set);
							continue;
						} else {
							Write(i, buf, strlen);
						}
					}
				}
			}
		}
	}
}

