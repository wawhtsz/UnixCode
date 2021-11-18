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

int count = 0;

void *thread_func(void *arg) {
	printf("in %dth thread: thread id is %lu, process id is %u, count = %d\n", (int)arg, pthread_self(), getpid(), count);
	count ++;
}


int main() {

	int ret;
	pthread_t tid;
	int i = 0;
	for(i; i < 50; i++) {
		ret = pthread_create(&tid, NULL, thread_func, (void *)i);
		if(ret != 0) {
			printf("create thread error\n");
		}	
	}
	printf("in main: thread id is %lu, process id is %u, count = %d\n", pthread_self(), getpid(), count);
	
	pthread_exit(NULL);

}
