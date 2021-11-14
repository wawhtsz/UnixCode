/*************************************************************************
    > File Name: sigpending.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sun Nov 14 15:32:39 2021
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>

void print_pending(sigset_t *ped) {
	int i = 1;
	for(i; i < 32; i++) {
		if(sigismember(ped, i) == 1) {
			putchar('1');
		} else {
			putchar('0');
		}
	}
	printf("\n");

}

/* 打印未决信号集 */
int main() {
	sigset_t myset, oldset, ped;

	sigemptyset(&myset);
	sigaddset(&myset, SIGQUIT); /* 屏蔽3号信号,键盘使用  Ctrl + \  */  
	sigaddset(&myset, SIGINT); //屏蔽2号信号， Ctrl + c
	sigaddset(&myset, SIGTSTP); // 屏蔽20号信号，Ctrl + z

	/* 设置信号屏蔽字 */
	if(sigprocmask(SIG_BLOCK, &myset, &oldset) == -1) { 
		perror("sigprocmask");
		exit(1);
	}
	while(1) {
		sigpending(&ped);
		print_pending(&ped);
		sleep(1);
	}
	return 0;
}
