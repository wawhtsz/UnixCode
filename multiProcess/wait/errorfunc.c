/*************************************************************************
    > File Name: errrofunc.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Wed Nov 10 09:50:11 2021
 ************************************************************************/

//一个会发生段错误的程序

#include<stdio.h>

int main() {
	int i = 0;
	printf("please inset:");
	scanf("%d", i);
	printf("%d\n", i);
	return 0;
}
