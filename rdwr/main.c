//本函数实现从src.txt 中读取所有内容输出到  dst.txt 中
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	int fdsrc = 0; //文件描述符
	int fddst = 0;

	char buf[30]; //缓冲区
	
	char srcfile[30];//原文件名称
	char dstfile[30];//目标文件名称
	

	printf("Please insert the source file name:");
	scanf("%s", srcfile);
	printf("Please insert the dst file name:");
	scanf("%s", dstfile);

	//打开文件
	fdsrc = open(srcfile, O_RDONLY);
	if(fdsrc == -1) {
		perror("open file faild");
		exit(1);
	}
	fddst = open(dstfile, O_WRONLY | O_TRUNC);
	if(fddst == -1) {
		perror("open dstfile faild");
		exit(1);
	}
	//读取文件内容
	
	int count = 0;//统计读出的字符
	while(count = read(fdsrc, buf, sizeof(buf)) > 0) {
		if(write(fddst, buf, count) == -1) {
			perror("write file faild");
			exit(1);
		}
	}
	//关闭文件
	if(close(fdsrc) == -1) {
		perror("close srcfile faild");
		exit(1);
	}
	if(close(fddst) == -1) {
		perror("close dstfile faild");
		exit(1);
	}	
	return 0;	
}
