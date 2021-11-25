/*************************************************************************
    > File Name: server.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Tue Nov 23 19:06:29 2021
    > Description: 多进程并发服务器
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>

#include"wrap.h"

#define CLNTNUM 5


void wait_child(int signo) {
	while(waitpid(0, NULL, WNOHANG) > 0) {
		printf("one client exit\n");
	}
}

int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf("insert <port>\n");
		exit(1);

	}

	signal(SIGCHLD, wait_child);

	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_len;

	serv_sock = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	Bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	Listen(serv_sock, CLNTNUM);

	pid_t pid;
	while(1) {
		clnt_addr_len = sizeof(clnt_addr);
		clnt_sock = Accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_len);
		char buf[BUFSIZ];
		printf("IP:%s, port:%d\n", 
				inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, buf, sizeof(buf)),
				ntohs(clnt_addr.sin_port));

		pid = fork();
		if(pid == 0) {
			Close(serv_sock);
			break;
		} else if(pid > 0) {
			Close(clnt_sock);
		} else {
			perror("fork");
			exit(1);
		}
	}

	if(pid == 0) {
		char buf[BUFSIZ];
		int count;
		while(1) {
			count = Read(clnt_sock, buf, sizeof(buf));
			if(count == 0) {
				Close(clnt_sock);
				break;
			}
			int i = 0;
			for(; i < count; i++) {
				buf[i] = toupper(buf[i]);
			}
			Write(clnt_sock, buf, count);
		}
	}
	return 0;
}

