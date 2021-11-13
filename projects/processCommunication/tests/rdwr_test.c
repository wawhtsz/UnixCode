/*************************************************************************
    > File Name: rdwr_test.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 18:34:06 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>

struct onlin {
	int pid;
	int src;
	int dst;
	char buff[20];
};
int main() {
	int fd;
	struct onlin on;
	on.pid = 1;
	on.src = 2;
	on. dst = 3;
	strcpy(on.buff, "helloworld!");
	fd = open("./zero", O_RDWR);
	if(fd == -1) {
		perror("open");
		exit(1);
	}
	if(write(fd, &on, sizeof(on)) == -1){
		perror("write");
		exit(1);
	}
	if(write(fd, &on, sizeof(on)) == -1){
		perror("write");
		exit(1);
	}
	printf("%d\n", lseek(fd, 0, SEEK_SET));
	int count = 0;
	struct onlin in;
	count = read(fd, &in, sizeof(in));
	printf("%d\n", count);
	if( count == -1){
		perror("read");
		exit(1);
	}
	printf("%d,%d,%d,%s", in.pid, in.src, in.dst, in.buff);
	return 0;
}
