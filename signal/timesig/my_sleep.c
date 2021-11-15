/*************************************************************************
    > File Name: my_sleep.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov 15 08:20:44 2021
	> 利用alarm和pause函数实现sleep函数
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<errno.h>

#define SIGSUSPEND
void func(int signo) {
	printf("alarm\n");
}

/* 不使用sigsuspend 仅仅使用pause
 * 会产生时序竞态问题 */
#ifndef SIGSUSPEND
unsigned int my_sleep(unsigned int time) {

	struct sigaction act, oldact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	int ret;
	ret = sigaction(SIGALRM, &act, &oldact);
	if(ret == -1) {
		perror("sigaction");
		exit(1);
	}
	
	alarm(time);
	ret = pause();
	if(ret == -1 && errno == EINTR) {
		printf("pause\n");
	}
	printf("woke\n");

	ret = alarm(0);                         //恢复
	sigaction(SIGALRM, &oldact, NULL);
	return ret;
}

/* 使用sigsuspend函数解决时序竞态问题 */
#else

unsigned int my_sleep(unsigned int time) {
	struct sigaction act, oldact;
	sigset_t newmask, oldmask, susmask;
	int ret;

	/* 初始化act
	 * 注册捕获函数*/
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);	
	act.sa_flags = 0;
	sigaction(SIGALRM, &act, &oldact);

	/* 设置信号屏蔽集，将SIGALRM信号屏蔽
	 * 防止在alarm调用后CPU被抢占而可能造成的时序竞态
	 * 即在CPU被抢占期间alarm到时间发出SIGALRM信号
	 * 导致继续执行先处理信号造成pause无限等待 */
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGALRM);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);

	alarm(time);

	/* 原信号屏蔽字可能屏蔽了 SIGALRM
	 * 设置以保证可以解除对 SIGALRM的屏蔽 */
	susmask = oldmask;
	sigdelset(&susmask, SIGALRM);
	sigsuspend(&susmask);

	/* 恢复屏蔽字和信号处理函数 */
	sigprocmask(SIG_BLOCK, &oldmask, NULL);
	sigaction(SIGALRM, &oldact, NULL);
	
	ret = alarm(0);
	return ret;
}


#endif
int main() {
	int i = 0;
	for(; i < 10; i++) {
		my_sleep(3);
		printf("-------------\n");
	}
	my_sleep(1);
	return 0;
}
