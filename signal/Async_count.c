/*************************************************************************
    > File Name: Async_count.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov 15 18:46:29 2021
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int n;
int flag;

void do_sig_child(int signo) {
	printf("I'm chilid, my pid is %d, n = %d\n", getpid(), n);
	n += 2;
	flag = 1;
	//sleep(1);
}

void do_sig_parent(int signo) {
	printf("I'm parent, my pid is %d, n = %d\n", getpid(), n);
	n += 2;
	flag = 1;
	//sleep(1);
}

int main() {
	struct sigaction act, oldact;
	pid_t pid = 0;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	pid = fork();

	if(pid == -1) {
		perror("fork");
		exit(1);
	} else if(pid > 0) {
		n = 1;
		act.sa_handler = do_sig_parent;
		sigaction(SIGUSR1, &act, NULL);
		printf("parent------\n");
		sleep(1);
		printf("parent------\n");
		do_sig_parent(1);
		while(1) {
			/* 如果父进程已经打印完成则通知子进程 */
			if(flag == 1) {
				kill(pid, SIGUSR2);
				flag = 0;
			}
		}
	} else {
		n = 2;
		act.sa_handler = do_sig_child;
		sigaction(SIGUSR2, &act, NULL);
		printf("child----------\n");
		sleep(1);
		while(1) {
			/* 如果子进程已经打印完成则通知父进程 */
			if(flag == 1) {
				kill(getppid(), SIGUSR1);
				flag = 0;
			}
		}
	}

}
