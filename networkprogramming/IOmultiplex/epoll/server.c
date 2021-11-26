/*************************************************************************
    > File Name: server.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Fri Nov 26 08:52:42 2021
    > Description: 
 ************************************************************************/

#include<stdio.h>
#include<sys/epoll.h>

#include"wrap.h"

#define BUFSIZE 100
#define EPOLLSIZE 50

int main(int argc, char *argv[]) {

	int serv_sock, clnt_sock;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	int str_len, i;
	char buf[BUFSIZE];
	int ret;

	int epfd, event_cnt;
	struct epoll_event events[EPOLLSIZE];
	struct epoll_event event;

	if(argc != 2) {
		printf("Usage: <port>\n");
		exit(1);
	}

	serv_sock = Socket(AF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));
	Bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	Listen(serv_sock, 10);

	epfd = epoll_create(EPOLLSIZE);
	event.events = EPOLLIN;
	event.data.fd = serv_sock;
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, serv_sock, &event);
	if(ret == -1) {
		perror("epoll_ctl error\n");
		exit(1);
	}

	while(1) {
		event_cnt = epoll_wait(epfd, events, EPOLLSIZE, -1);
		if(event_cnt == -1) {
			perror("epoll_wait error\n");
			exit(1);
		}

		for(i = 0; i < event_cnt; i++) {
			if(events[i].data.fd == serv_sock) {
				clnt_addr_size = sizeof(clnt_addr);
				clnt_sock = Accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);

				event.events = EPOLLIN;
				event.data.fd = clnt_sock;
				ret = epoll_ctl(epfd, EPOLL_CTL_ADD, clnt_sock, &event);

				printf("connected client: %d\n", clnt_sock);

			} else {
				str_len = Read(events[i].data.fd, buf, sizeof(buf));
				if(str_len == 0) {
					ret = epoll_ctl(epfd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
					Close(events[i].data.fd);
					printf("closed client: %d\n", events[i].data.fd);
				} else {
					Write(events[i].data.fd, buf, str_len);
				}
			}
		}
	}
	close(serv_sock);
	close(epfd);
	return 0;
}
