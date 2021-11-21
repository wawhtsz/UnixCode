/*************************************************************************
    > File Name: server.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sun Nov 21 19:26:21 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<ctype.h>
#include<stdlib.h>


#define PORT 6666

int main() {

	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_len = sizeof(clnt_addr);
	char buf[BUFSIZ];

	
	serv_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1) {
		perror("socket");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(PORT);
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
		perror("bind");
		exit(1);
	}

	if(listen(serv_sock, 5) == -1) {
		perror("listen");
		exit(1);
	}

	printf("connecting \n");
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_len);
	if(clnt_sock == -1){
		perror("accept");
		exit(1);
	}
	printf("connect %d\n", clnt_sock);

	while(1) {
		int count = 0;
		count = read(clnt_sock, buf, sizeof(buf));
		if(count == 0)
			break;
		int i = count;
		for(;i > 0; i--) {
			buf[i - 1] = toupper(buf[i - 1]);
		}
		write(clnt_sock, buf, count);
	}

	close(serv_sock);
	close(clnt_sock);
	return 0;
}
