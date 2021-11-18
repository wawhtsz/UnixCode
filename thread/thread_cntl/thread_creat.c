/*************************************************************************
    > File Name: thread_creat.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 18 08:39:59 2021
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>


void *thread_func(void *arg) {
	printf("in thread: thread id is %lu, process id is %u\n", pthread_self(), getpid());

}

int main() {

	int ret;
	pthread_t tid;
	printf("in main: thread id is %lu, process id is %u\n", pthread_self(), getpid());
	ret = pthread_create(&tid, NULL, thread_func, NULL);
	if(ret != 0) {
		printf("create thread error\n");
	}
	sleep(1);
	printf("in main: thread id is %lu, process id is %u\n", pthread_self(), getpid());

}
