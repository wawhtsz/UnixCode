/*************************************************************************
    > File Name: echo_server.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov 22 08:24:39 2021
    > Description: echo server 
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main(int argc, char *argv[]) {

	/* 判断是否正确输入端口 */
	if(argc != 2) {
		printf("Please input <port>\n");
		exit(1);
	}

	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_len;
	char buf[BUFSIZ];

	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1) {
		perror("socket\n");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("bind");
		exit(1);
	}

	if(listen(serv_sock, 5) == -1) {
		perror("listen");
		exit(1);
	}

	clnt_addr_len = sizeof(clnt_addr);
	int count = 0;
	int i = 5;
	for(; i > 0; i--) {
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_len);
		if(clnt_sock == -1) {
			perror("accept");
			exit(1);
		}

		char clnt_ip[BUFSIZ];
		printf("client IP:%s, port:%d\n", 
				inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_ip, sizeof(clnt_ip)),
				ntohs(clnt_addr.sin_port));

		while((count = read(clnt_sock, buf, sizeof(buf))) != -1) {
			if(count == 0)
				continue;
			if(write(clnt_sock, buf, count) != count) {
				perror("write");
				exit(1);
			}
		}

		close(clnt_sock);
	}
	close(serv_sock);
	return 0;



}

