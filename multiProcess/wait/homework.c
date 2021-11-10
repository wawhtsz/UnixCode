/*************************************************************************
    > File Name: homework.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Wed Nov 10 09:47:18 2021
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main() {
	pid_t pid[3], target[3];
	int status[3];
	int i = 0;
	for(; i < 3; i++) {
		pid[i] = fork();
		if(pid[i] == -1) {
			perror("create process faild\n");
			exit(EXIT_FAILURE);
		} else if(pid[i] > 0) {

		} else {
			target[i] = pid[i];
			break;
		}
	}
	if(i < 3) { //子进程
		int funcstatus = 0;//保存exec函数调用返回结果
		
		if(i == 0) {
			sleep(1);
			//调用  ps 命令
			funcstatus = execlp("ps", "ps", "a", NULL);
		} else if(i == 1) {
			sleep(3);
			char buf[70];//保存当前目录绝对路径
			if(getcwd(buf, sizeof(buf)) == NULL) {
				perror("getcwd");
				exit(EXIT_FAILURE);
			}
			funcstatus = execlp(strcat(buf, "/normalfunc"),"normal", NULL);
			if(funcstatus == -1) {
				perror("exec");
				exit(EXIT_FAILURE);
			}
		} else {
			sleep(5);
			char buf[70];//保存当前目录绝对路径
			if(getcwd(buf, sizeof(buf)) == NULL) {
				perror("getcwd");
				exit(EXIT_FAILURE);
			}
			funcstatus = execlp(strcat(buf, "/errorfunc"),"error", NULL);
			if(funcstatus == -1) {
				perror("exec");
				exit(EXIT_FAILURE);
			}
		}
	} else { //父进程
		sleep(10);
		int j = 0;
		for(; j < 3; j++) {
			if(waitpid(target[j], status + j, 0) == -1) {
				perror("waitpid");
				exit(EXIT_FAILURE);
			} else {
				if(WIFEXITED(status[j])) {
					printf("child%d exit with %d\n", j, WEXITSTATUS(status[j]));
				} else if(WIFSIGNALED(status[j])) {
					printf("child%d killed by SIG%d\n", j, WTERMSIG(status[j]));
				}
			}
		}
	}
	return 0;
}
