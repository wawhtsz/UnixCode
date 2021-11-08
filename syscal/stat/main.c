/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov  8 18:37:26 2021
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

//练习  stat()相关函数的使用

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("./a.out filename\n");
		exit(1);
	}
	struct stat *fs;
	int fd;
	if((fd = open(argv[1], O_RDWR)) == -1) {
		perror("打开文件失败\n");
		exit(1);
	}
	if(fstat(fd, fs) == -1) {
		perror("读取文件信息失败\n");
		exit(1);
	}
	printf("file's inode is %d\n",fs->st_ino);
	printf("file size is %d\n", fs->st_size);

	if(close(fd) == -1) {
		perror("关闭文件失败");
		exit(1);
	}
	return 0;
}
 
