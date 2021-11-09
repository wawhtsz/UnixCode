/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov  8 20:05:32 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main() {

	int fd = open("hello", O_CREAT | O_RDWR, 0664);

	unlink("hello");

	write(fd, "hello",5);

	lseek(fd, 0, SEEK_SET);

	char buf[20] = {0};
	int count = read(fd, buf, sizeof(buf));

	write(1, buf, count);

	close(fd);
	return 0;
}
