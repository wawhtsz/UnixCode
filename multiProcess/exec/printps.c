/*************************************************************************
    > File Name: printps.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Tue Nov  9 18:41:23 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

int main() {
	pid_t pid;
	int fd;
	fd = open("./dst.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(fd == -1) {
		perror("open file faild");
		exit(1);
	}	
	dup2(fd, STDOUT_FILENO);
	pid = fork();
	if(pid == -1) {
		perror("create child process faild");
		exit(1);
	}
	if(pid == 0) {
		execlp("ps", "ps","aux", NULL );//不返回，不用close(fd)关闭文件了

	} else {
		sleep(2);
		printf("father\n");
		close(fd);
	}
	return 0;
}
