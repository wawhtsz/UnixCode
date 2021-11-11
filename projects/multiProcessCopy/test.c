/*************************************************************************
    > File Name: test.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 11 21:14:22 2021
 ************************************************************************/

#include<stdio.h>

int main() {
	int i = 638;
	char *p =NULL;
	p =(char *) &i;
	printf("%d", *(int *)p);
	return 0;
}
