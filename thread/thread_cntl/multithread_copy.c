/*************************************************************************
    > File Name: multithread_copy.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 18 14:57:11 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>

/*
 * 默认拷贝src.txt文件到dst.txt文件
 * 输入参数 线程数量
 */

int main(int argc, char* argv[]) {

	if(argc != 2) {
		printf("Please insert correct num\n");
	}

	/* 线程数量 */
	int num = atoi(argv[1]);

	struct stat fs;
	int ret;
	int sfd,dfd;   //srcfd, dstfd

	sfd = open("src.txt", O_RDONLY);
	if(sfd == -1) {
		perror("open");
		exit(1);
	}

	fstat

	
}
