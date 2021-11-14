/*************************************************************************
    > File Name: alarm.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sun Nov 14 13:56:00 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

/* alarm定时 */
int main() {
	int i = 0;
	alarm(1);
	for(i;;i+=1)
		printf("%d\n",i);
	return 0;
}

