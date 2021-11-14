/*************************************************************************
    > File Name: myalarm.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sun Nov 14 14:16:10 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<fcntl.h>

unsigned int my_alarm(int time) {
	struct itimerval cur,old;
	cur.it_value.tv_sec = time;
	cur.it_value.tv_usec = 0;
	cur.it_interval.tv_usec = 0;
	cur.it_interval.tv_sec = 0;
	if(setitimer(ITIMER_REAL, &cur, &old) == -1) {
		perror("setitimer");
		exit(1);
	}
	return old.it_value.tv_sec;
}

int main() {
	int i = 0;
	my_alarm(1);
	for(i; ; i++) {
		printf("%d\n", i);
	}
	return 0;
}
