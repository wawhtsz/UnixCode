/*************************************************************************
    > File Name: sigaction.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sun Nov 14 16:17:53 2021
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void catch(int signo) {
	printf("sig %d is caught\n", signo);
	sleep(5);
	printf("------finish---------\n");
}

int main() {
	sigset_t sigmask;
	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGINT);

	struct sigaction act, oldact;
	act.sa_handler = catch;
	act.sa_mask = sigmask;
	act.sa_flags = 0;

	if(sigaction(SIGQUIT, &act, &oldact) == -1) {
		perror("sigaction");
		exit(0);
	}
	while(1);
	return 0;

}
