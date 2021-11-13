/*************************************************************************
    > File Name: test.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 10:46:41 2021
 ************************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

struct stp {
	int id;
	char *p;
};

struct stv {
	int id;
	char v[30];
};

int main() {
	struct stp p;
	p.id = 1;
	printf("p.id size is:%d\n", sizeof(p.id));
	printf("p.p size is:%d\n", sizeof(p.p));
	printf("p origin size is:%d\n", sizeof(p));
	struct stv v;
	v.id = 2;
	printf("v.id size is:%d\n", sizeof(v.id));
	printf("v.v size is:%d\n", sizeof(v.v));
	printf("v origin size is:%d\n", sizeof(v));

	p.p = "hello";
	strcpy(v.v, "hello");
	printf("p size is: %d\n", sizeof(p));
	printf("v size is: %d\n", sizeof(v));
	return 0;
}
