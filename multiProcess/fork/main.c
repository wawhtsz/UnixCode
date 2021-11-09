/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Tue Nov  9 15:14:37 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main() {
	printf("before---------\n");

	pid_t pid;
	int num = 1; 
	for(; num <= 5; num++) {
		pid = fork();
		if(pid == -1) {
			perror("create process faild");
			exit(1);
		} else if(pid == 0) {
			printf("num = %d, child process, pid = %u, ppid = %u\n", num, getpid(), getppid());
			break;
		} else {
			printf("parent process, pid = %u, ppid = %u\n", getpid(), getppid());
			sleep(1);
		}
	}	
	printf("after----------\n");
	
}
