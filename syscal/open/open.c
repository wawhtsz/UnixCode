#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
	int fd;
	//打开已经存在的文件
	fd = open("wenjian.txt", O_RDWR);
	if(fd == -1) {
		perror("open file");
		exit(1);
	}
	//关闭文件
	int ret = close(fd);
	printf("ret = %d\n", ret);

	//创建新文件
	fd = open("newfile.txt", O_CREAT | O_RDWR, 777);
	if(fd == -1) {
		perror("create file");
		exit(1);
	}
	ret = close(fd);
	if(ret == 0)
		printf("close file %d succeed\n", fd);
	//关闭文件
	ret = close(fd);
	printf("ret = %d\n", ret);
	//打开文件截断
	fd = open("wenjian.txt", O_RDWR | O_TRUNC);
	if(fd == -1) {
		perror("open file");
		exit(1);
	}

	
	return 0;
}
