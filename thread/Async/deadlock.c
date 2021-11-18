/*************************************************************************
    > File Name: deadlock.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 18 18:02:20 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>


pthread_mutex_t mutexA;
pthread_mutex_t mutexB;


void *thread_func() {

	pthread_mutex_lock(&mutexA);
	printf("thread got mutextA\n");
	sleep(2);
	pthread_mutex_lock(&mutexB);
	printf("thread got mutextB\n");

	printf("I have got two mutex!\n");

	pthread_mutex_unlock(&mutexB);
	pthread_mutex_unlock(&mutexA);
}


int main() {

	/* 初始化两把锁 */
	int ret;
	ret = pthread_mutex_init(&mutexA, NULL);
	if(ret != 0) {
		perror("pthread_mutex_init mutexA");
		exit(1);
	}
	ret = pthread_mutex_init(&mutexB, NULL);
	if(ret != 0) {
		perror("pthread_mutex_init mutexB");
		exit(1);
	}

	/* 创建线程 */
	pthread_t tid;
	ret = pthread_create(&tid, NULL, thread_func, NULL);
	if(ret != 0) {
		perror("pthread_create");
		exit(1);
	}

	pthread_mutex_lock(&mutexB);
	printf("main got mutextB\n");
	sleep(2);
	pthread_mutex_lock(&mutexA);
	printf("main got mutextA\n");

	printf("I have got two mutex!\n");

	pthread_mutex_unlock(&mutexA);
	pthread_mutex_unlock(&mutexB);


	pthread_mutex_destroy(&mutexA);
	pthread_mutex_destroy(&mutexB);


	return 0;


}
