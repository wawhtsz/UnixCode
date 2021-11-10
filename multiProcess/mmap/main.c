/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Wed Nov 10 17:50:13 2021
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include<fcntl.h>

#define	ANONYMOUS

#ifndef ANONYMOUS //命名映射区
int main() {
	int fd;
	int status;
	fd = open("./mmap.txt", O_RDWR | O_CREAT , 0644);
	if(fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	int len = 1024;
	if(ftruncate(fd, len) == -1) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}
	char *p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	strcpy(p, "abc");
	if(munmap(p, len) == -1) {
		perror("munmap");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return 0;
}
#else //匿名映射区
	int var = 100;

int main() {
	char *p;//映射区地址
	int len = 5;//映射区大小
	p = mmap(NULL, 5, PROT_WRITE | PROT_READ, MAP_ANONYMOUS | MAP_SHARED, -1, 0);
	if(p == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	pid_t pid;
	pid = fork();
	if(pid > 0) {
		sleep(2);
		printf("%s, %d\n", p, var);
		if(munmap(p, len) == -1) {
			perror("munmap");
			exit(EXIT_FAILURE);
		}
	} else {
		strcpy(p,"abcd");
		var = 999;
		printf("%s, %d\n", p, var);
		if(munmap(p, len) == -1) {
			perror("munmap");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}



#endif
