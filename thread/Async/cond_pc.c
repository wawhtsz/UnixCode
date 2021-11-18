/*************************************************************************
    > File Name: cond_pc.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 18 19:16:32 2021
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>

struct msg {
	int num;
	struct msg* next;
};

struct msg* head = NULL;  //链表头
struct msg* mp = NULL;    //链表当前节点

/* 锁和条件变量的静态初始化 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *productor(void* arg) {

	int ret = 0;

	while(1) {

		/* 加入队列 */
		ret = pthread_mutex_lock(&mutex);
		if(ret != 0) {
			printf("productor lock error\n");
			exit(1);
		}

		/* 生产 */
		mp = (struct msg*)malloc(sizeof(struct msg));
		mp->num = rand() % 500 + 1;
		mp->next = NULL;
		printf("---------productor %d\n", mp->num);

		mp->next = head->next;
		head->next = mp;

		ret = pthread_mutex_unlock(&mutex);
		if(ret != 0) {
			printf("productor unlock error\n");
			exit(1);
		}

		pthread_cond_signal(&cond);
		if(ret != 0) {
			printf("productor signal error\n");
			exit(1);
		}
		sleep(rand() % 5);
	}
}

void *consumer(void* arg) {

	int ret = 0;
	while(1) {
		ret = pthread_mutex_lock(&mutex);
		if(ret != 0) {
			printf("consumer lock error\n");
			exit(1);
		}
		while(head->next == NULL) {
			/* 等待条件 */
			ret = pthread_cond_wait(&cond, &mutex);
			if(ret != 0) {
				printf("consumer wait error\n");
				exit(1);
			}
		}

		/* 消费 */
		head->next = mp->next;
		printf("-------------consumer %d\n", mp->num);
		free(mp);
		mp = head->next;

		ret = pthread_mutex_unlock(&mutex);
		if(ret != 0) {
			printf("consumer unlock error\n");
			exit(1);
		}
		
		sleep(rand() % 5);
	}

}

/* 条件变量实现的生产者消费者模型 */
int main() {
	head =(struct msg*)malloc(sizeof(struct msg));
	head->next = NULL;

	srand(time(NULL));  //随机生产

	pthread_t pid;// 生产者
	pthread_t cid;// 消费者

	int ret = 0;
	ret = pthread_create(&pid, NULL, productor, NULL);
	if(ret != 0) {
		printf("pthread_create productor error\n");
		exit(1);
	}
	ret = pthread_create(&cid, NULL, consumer, NULL);
	if(ret != 0) {
		printf("pthread_create consumer error\n");
		exit(1);
	}


	ret = pthread_join(pid, NULL);
	if(ret != 0) {
		printf("pthread_join productor error\n");
		exit(1);
	}
	ret = pthread_join(cid, NULL);
	if(ret != 0) {
		printf("pthread_join consumer error\n");
		exit(1);
	}

	return 0;
}
