/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Tue Nov  9 09:23:11 2021
 ************************************************************************/

//打印环境变量的一个小程序，功能同  env  相同
#include<stdio.h>

extern char **environ; //环境变量表

int main() {
	int i = 0;
	for(i; environ[i] != NULL; i++) {
		printf("%s\n",environ[i]);
	}
	return 0;
}
