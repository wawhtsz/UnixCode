/*************************************************************************
    > File Name: input_test.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 14:47:35 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main(){
	int fd = 0;
	char buf[3];
	int count = 0;
	int i = 10;
	for(; i > 0; i--){
		count = read(STDIN_FILENO, buf, sizeof(buf));
		if(count == -1) {
			perror("read");
			exit(1);
		}

		count = write(STDOUT_FILENO, buf, count);
		if(count == -1) {
			perror("read");
			exit(1);
		}	
	}
	return 0;
}
