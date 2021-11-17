/*************************************************************************
    > File Name: recordTime.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Wed Nov 17 09:17:53 2021
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
#include<string.h>

/* 创建守护进程周期向文件写入时间 */
int main() {
	pid_t pid;
	int ret;

	/* 创建子进程 结束父进程 */
	pid = fork();
	if(pid == -1) {
		perror("fork");
		exit(1);
	}
	if(pid > 0)
		return 0;

	/* 创建新的会话 */
	pid = setsid();
	if(pid == -1) {
		perror("setsid");
		exit(1);
	}

	/* 改变工作目录 */
	/* 改变 umask */
	/* 这里就不变了 */

	/* 重定向文件描述符 */
	int fd;
	close(STDIN_FILENO);
	fd = open("/dev/null", O_RDONLY);
	if(fd == -1) {
		perror("open");
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	dup2(fd, STDERR_FILENO);

	/* 守护进程主逻辑 */
	/* 打开写入的文件 */
	fd = open("./time", O_WRONLY | O_CREAT, 0644);
	if(fd == -1) {
		perror("open time");
		exit(1);
	}
	
	/* 周期性写入时间 */
	time_t now;
	//dup2(fd, STDOUT_FILENO);
	char buf[64];
	while(1) {
		if(time(&now) == -1) {
			perror("time");
			exit(1);
		}
		//printf("%s", ctime(&now));
		strcpy(buf, ctime(&now));
		if(write(fd, buf, strlen(buf) ) == -1) {
			perror("write");
			exit(1);
		}
		sleep(3);
	}

}
