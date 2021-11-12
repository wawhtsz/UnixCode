/*************************************************************************
    > File Name: do_copy.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 11 18:20:16 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>


#define BUFSIZE 1024

/* 完成拷贝，argv[1]是共享内存指针，argv[2]是长度，argv[3]是目标文件 , argv[4]是偏移 */
int main(int argc, char*argv[]) {
	if(argc != 5) {
		printf("arg error");
		exit(1);
	}

	int fd = open(argv[3], O_WRONLY);
	if(fd == -1) {
		perror("open");
		exit(1);
	}
	int off = atoi(argv[4]);
	if(lseek(fd, off, SEEK_SET) != off) {
			perror("lseek");
			exit(1);
		}

	char buf[BUFSIZE];
	int  restLen = atoi(argv[2]); //剩余要写的长度
	while(restLen != 0) {
		int writeLen = 0; //本次要写的长度
		int offset = off;//本次读的起始偏移
		if(restLen < BUFSIZE) {
			writeLen = restLen; 
			restLen = 0;
		} else {
			writeLen = BUFSIZE;
			restLen = restLen - BUFSIZE;
		}
		strncpy(buf, argv[1] + offset, writeLen);
		if(write(fd, buf, writeLen) != writeLen) {
			perror("write");
			exit(1);
		}
		offset += writeLen;
	}
	close(fd);
	return 0;

}
