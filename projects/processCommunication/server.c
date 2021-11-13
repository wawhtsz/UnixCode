/*************************************************************************
    > File Name: server.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 09:47:40 2021
 ************************************************************************/

#include"server.h"

struct onlinePID PIDLIST;

void add_tail(pid_t pid) {
	struct onlinePID *p =(struct onlinePID*) malloc(sizeof(struct onlinePID));
	struct onlinePID *ptr = &PIDLIST;
	while(ptr->next != NULL) {
		ptr = ptr->next;
	}
	p->pre = ptr;
	ptr->next = p;
	p->next = NULL;
	p->pid = pid;
	p->fd = create_special_fifo(pid, 1);
}

void remove_PID(pid_t pid) {
	struct onlinePID *ptr = PIDLIST.next;
	while(ptr->pid != pid) {
		ptr = ptr->next;
	}
	ptr->pre->next = ptr->next;
	ptr->next->pre = ptr->pre;
	close(ptr->fd);
	free(ptr);
}

void retransmit(struct msg *message) {
	struct onlinePID *ptr = &PIDLIST;
	int fd = -1;
	while(ptr->next != NULL) {
		ptr = ptr->next;
		if(ptr->pid == message->dstPID) {
			fd = ptr->fd;
			break;
		}
	}
	if(fd == -1) {
		return;
	}
	if(write(fd, message, sizeof(*message)) != sizeof(*message)) {
		perror("write");
		exit(EXIT_FAILURE);
	}
}
int main() {
	int cfifo;
	cfifo = open_common_fifo(1);
	struct msg message;
	int count = 0;
	while((count = read(cfifo, &message, sizeof(message))) != 0) {
		if(count == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		if(message.type == SYN) {
			add_tail(message.srcPID);
		} else if(message.type == FIN) {
			remove_PID(message.srcPID);
		} else {
			retransmit(&message);
		}
	}
}



