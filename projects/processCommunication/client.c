/*************************************************************************
    > File Name: client.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 15:33:24 2021
 ************************************************************************/

#include"client.h"


#define SFIFO fd[0] //special FIFO
#define CFIFO fd[1] //common FIFO

int dstPID = 0;

int main() {
	int fd[2];
	printf("Please insert dstPID:");
	scanf("%d", &dstPID);
	login(fd);
	while(1) {
		receive(SFIFO);
		send(CFIFO);
	}
	return 0;
}

void login(int fd[2]) {
	CFIFO = open_common_fifo(0);
	SFIFO = create_special_fifo(getpid(), 0);
	struct msg message;
	create_msg(SYN, SYN_DST_PID, "\n", &message);
	if(write(CFIFO, &message, sizeof(message)) == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}
}

void receive(int fd) {
	struct msg message;
	int count = 0;
	while((count = read(fd, &message, sizeof(message))) != 0) {
		printf("%d:%s", message.srcPID, message.data);	
	}
}




void send(int fd) {
	char data[BUF_SIZE];
	int count = 0;
	if((count = read(STDIN_FILENO, data, sizeof(data))) != 0) {
		while(count != 0) {
			if(count == -1) {
				perror("read");
				exit(EXIT_FAILURE);
			}
			struct msg message;
			create_msg(MSG, dstPID, data, &message);
			if(write(fd, &message, sizeof(message)) == -1) {
				perror("write");
				exit(EXIT_FAILURE);
			}
			count =  read(STDIN_FILENO, data, sizeof(data));
		}
	}
}
