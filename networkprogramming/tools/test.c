/*************************************************************************
    > File Name: test.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Tue Nov 23 09:33:19 2021
    > Description: 
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include"wrap.h"

int main() {
	int sfd;
	sfd = open("src.txt", O_RDONLY);
	if(sfd == -1) {
		perror("open");
		exit(1);
	}

	char buf[BUFSIZ];
	//read(sfd, buf, sizeof(buf));
	//printf("%s", buf);
	int i = 5;
	for(; i > 0; i--) {
		Readline(sfd, buf);
		printf("%s", buf);
	}

	close(sfd);

}
