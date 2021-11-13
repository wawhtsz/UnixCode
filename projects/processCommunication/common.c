/*************************************************************************
    > File Name: common.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 10:27:50 2021
 ************************************************************************/

#include<stdio.h>
#include"common.h"

void create_msg(int type, int dstPID, char data[], struct msg *message) {
	message->type = type;
	message->srcPID = getpid();
	message->dstPID = dstPID;
	strcpy(message->data, data);
};

/* 
 * 功能：创建并打开用户专用fifo 
 * 返回值：成功返回fd
 *
 */
int create_special_fifo (int srcPID, int is_server) {
	int fd;
	char path[20] ;
	sprintf(path,"./%dFIFO", srcPID);
	if(is_server) {
		fd = open(path, O_WRONLY);
	} else {
		if(mkfifo(path, 0644) == -1) {
			perror("mkfifo");
			exit(EXIT_FAILURE);
		}
		fd = open(path, O_RDONLY);
	}
	if(fd == -1) {
		perror("open fifo");
		exit(EXIT_FAILURE);
	}
	return fd;
}


/* 
 * 功能：并打开公用fifo 
 * 返回值：成功返回fd
 *
 */
int open_common_fifo (int is_read) {
	int fd;
	if(is_read == 1) {
		/*if(mkfifo(COMMON_FIFO, 0644)) {
			perror("mkfifo");
			exit(EXIT_FAILURE);
		}*/
		fd = open(COMMON_FIFO, O_RDONLY);
	} else {
		fd = open(COMMON_FIFO, O_WRONLY);
	}
	if(fd == -1) {
		perror("open common fifo");
		exit(EXIT_FAILURE);
	}
	return fd;
}
















