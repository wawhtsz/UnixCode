/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Wed Nov 10 08:23:47 2021
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]) {

	int n = 5;
	if(argc == 2) {
		n = atoi(argv[1]);
	}

	pid_t pid, target_pid;
	int i = 0;
	for(; i < n; i++) {
		pid = fork();
		if(pid == -1) {
			perror("create process faild");
			exit(1);
		}
		if(pid == 0) {
			break;    //子进程退出
		} else {

		}
	}
	if(i == n) {
		sleep(n + 1);
		int status = -1;
		int j = 0;
		for(; j < n; j++) {
			while((target_pid = waitpid(-1, &status, WNOHANG)) == 0);
			if(target_pid == -1) {
				perror("wait child faild\n");
				exit(1);
			}
			printf("wait child%d success, he exit whit %d\n", target_pid, status);
		}
		printf("all child has been waitted\n");
		//while(1);
	} else {
		sleep(i);
		printf("I'am the %dth child, my pid is %d, my father's pid is %d\n", i + 1, getpid() ,getppid());
	}
	printf("%d\n", i);
	return 0;
}
