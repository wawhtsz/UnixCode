#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	//argv[0] 存放原文件，argv[1]存放目的文件

	//打开文件
	int fdsrc = open(argv[1], O_RDWR);
	if(fdsrc == -1) {
		perror("open srcfile faild");
		exit(1);
	}

	//获取文件大小
	int count = lseek(fdsrc, 0, SEEK_END);
	printf("the srcfile size is %d\n",count);
	
	//扩展文件
	int ret = lseek(fdsrc, 2000, SEEK_END);
	write(fdsrc, "end", 3);
	printf("after exetend the file's size is %d\n");

	close(fdsrc);
	return 0;
}
