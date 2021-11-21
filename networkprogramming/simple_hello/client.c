/*************************************************************************
    > File Name: client.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sun Nov 21 20:59:29 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 6666
#define SERV_ADDR "127.0.0.1"

int main() {
	int sock;
	struct sockaddr_in serv_addr;
	char buf[BUFSIZ];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1) {
		perror("socket");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(SERV_ADDR);
	serv_addr.sin_port = htons(PORT);

	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("connect");
		exit(1);
	}

	while(1) {
		scanf("%s", buf);
		write(sock, buf, strlen(buf));
		read(sock, buf, sizeof(buf));
		printf("%s\n", buf);
	}

	close(sock);
	return 0;
}
