/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Thu Nov 11 17:50:31 2021
 ************************************************************************/
#include<stdio.h>
#include<sys/mman.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define PROCESS_NUM 5

void print_error(char *p) {  //用于打印错误
	perror(p);
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
	/* 判断命令行参数是否正确*/
	if(argc != 3) {
		printf("Please insert correct argd\n");
		exit(1);
	}

	pid_t pid[PROCESS_NUM];
	char *p = NULL;
	int fd = 0;
	int writeLen = 0;
	struct stat srcStat;

	/* 打开原文件 */
	if((fd = open(argv[1], O_RDWR)) == -1) { 
		print_error("open");
	}

	/* 获得文件信息（长度）*/
	if((fstat(fd, &srcStat)) == -1) {
		print_error("fstat");
	}

	/* 原文件映射到共享内存 */
	p = mmap(NULL, srcStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(p == MAP_FAILED) {
		print_error("mmap");
	}
	close(fd);

	/* 计算每个子进程要写的长度 */ 
	writeLen = srcStat.st_size / PROCESS_NUM;

	/* 创建子进程 */
	int i = 0;
	for(; i < PROCESS_NUM; i++) {
		pid[i] = fork();
		if(pid[i] == -1) { //创建出错
			print_error("fork");
		} else if(pid[i] == 0) {    //子进程
			if(i == PROCESS_NUM - 1) {
				writeLen = srcStat.st_size - writeLen * i;
			}
			char path[90];
			if((getcwd(path, sizeof(path))) == NULL) {
				print_error("getcwd");
			}
			strcat(path, "/do_copy");
			if((execlp(path, "do_copy", p + writeLen * i,(int *) &writeLen, argv[2], NULL)) == -1) {
				print_error("execl");
			}

		} else {

		}
	}
	for(; i > 0; i--) {
		wait();
	}
	return 0;

}
