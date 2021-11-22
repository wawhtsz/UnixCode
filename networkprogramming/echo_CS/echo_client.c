/*************************************************************************
    > File Name: echo_client.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov 22 09:01:37 2021
    > Description: echo client
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("please inset <IP> <port>\n");
		exit(1);
	}

	int sock;
	struct sockaddr_in serv_addr;
	char buf[BUFSIZ];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1) {
		perror("socket");
		exit(1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("connect");
		exit(1);
	}

	while(1) {
		printf("Please input words(q to quit):");
		scanf("%s", buf);
		if(buf[0] == 'q' && strlen(buf) == 1)
			break;
		if(write(sock, buf, strlen(buf)) == -1) {
			perror("write");
			exit(1);
		}

		if(read(sock, buf, sizeof(buf)) == -1) {
			perror("read");
			exit(1);
		}

		printf("%s\n", buf);
	}

	close(sock);
	return 0;
}

