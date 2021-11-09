/*************************************************************************
    > File Name: execlp.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Tue Nov  9 17:45:12 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main() {
	pid_t pid;
	pid = fork();
	char buf[98];
	if(pid == -1) {
		perror("fork process faild\n");
		exit(1);
	}
	if(pid == 0) {
		/*if(execlp("ls","jlidsjfi", "-l", "-a", NULL) == -1) {
			perror("exec faild\n");
			exit(1);
		}*/
		if(execl("/bin/ls","ls", "/home/htsz" /*getcwd(buf, sizeof(buf))*/, "-l", NULL) == -1) {
			perror("exec faild\n");
			exit(1);
		}
	} else {
		sleep(1);
		printf("%s\n", getcwd(buf, sizeof(buf)));
		printf("%s---------%d", buf, strlen(buf));
	}
	return 0;
}

