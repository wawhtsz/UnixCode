/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Wed Nov 10 14:37:38 2021
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main() {
	int fd[2];
	pid_t pid;
	int status = 0;
	status = pipe(fd);
	if(status == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if(pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if(pid == 0) {
		close(fd[0]);//父进程写
		write(fd[1], "hello\n", strlen("hello\n"));
		close(fd[1]);
	} else {
		close(fd[1]);
		sleep(1);
		char buf[30];
		status = read(fd[0], buf, sizeof(buf));
		if(status == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		printf("%s,len is %d", buf, strlen("hello\n"));
	}
	return 0;
}
