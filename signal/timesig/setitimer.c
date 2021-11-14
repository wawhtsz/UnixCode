/*************************************************************************
    > File Name: setitimer.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sun Nov 14 14:47:22 2021
 ************************************************************************/

#include<stdio.h>
#include<sys/time.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void func(int signo) {
	printf("hello, world!\n");
}


int main() {
	struct itimerval it, oldit;
	signal(SIGALRM, func);   //注册SIG信号的捕捉处理信号

	it.it_value.tv_sec = 5;
	it.it_value.tv_usec = 0;
	it.it_interval.tv_sec = 3;
	it.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL, &it, &oldit) == -1) {
		perror("setitimer");
		exit(1);
	}

	while(1);
	return 0;
}
