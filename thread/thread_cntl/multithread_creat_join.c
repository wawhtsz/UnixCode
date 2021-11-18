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
#include<string.h>

#define NUM 5

typedef struct {
	int count;
	char str[30];
}retval;

void *thread_func(void *arg) {
	retval *rval = (retval*)arg;
	printf("count = %d, str = %s\n", rval->count, rval->str);
	rval->count++;
	sleep(3);
	pthread_exit((void *)rval);
}


int main() {
	retval *rval = (retval*)malloc(sizeof(retval));
	rval->count = 0;
	strcpy(rval->str, "hello\n");

	int ret;
	pthread_t tid[NUM];
	int i = 0;
	printf("start create thread\n");
	for(i; i < NUM; i++) {
		ret = pthread_create(&tid[i], NULL, thread_func, (void *)rval);
		if(ret != 0) {
			printf("create thread error\n");
		}	
	}
	
	printf("%d\n", i);
	sleep(2);

	for(i; i > 0; i--) {
		printf("-------------\n");
		if(pthread_join(tid[i], (void **)&rval) != 0) {
			printf("pthred_join error\n");
		}
		printf("thread id is %d, count = %d, str = %s\n", tid[i], rval->count, rval->str);
	}

	sleep(5);
	free(rval);
	
	pthread_exit(NULL);

}
