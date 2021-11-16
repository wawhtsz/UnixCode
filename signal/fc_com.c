/*************************************************************************
    > File Name: fc_com.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Tue Nov 16 15:30:39 2021
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>

void do_wait(int signo) {
	while(waitpid(0, NULL, WNOHANG) > 0) {
		;
	}

}

int main() {
	int fd[2];
	pid_t pid;
	int i = 10;

	if(pipe(fd) == -1) {
		perror("pipe");
		exit(1);
	}

	pid = fork();
	if(pid == 0) {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO); 
		execlp("grep", "grep", "f", NULL);

	} else{
		/* 屏蔽SIGCHLD信号 */
		sigset_t new, old;
		sigemptyset(&new);
		sigaddset(&new, SIGCHLD);
		if(sigprocmask(SIG_BLOCK, &new, &old) == -1) {
			perror("sigprocmask");
			exit(1);
		}

		/* 设置SIGCHLD捕捉函数 */
		struct sigaction act;
		act.sa_handler = do_wait;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		if(sigaction(SIGCHLD, &act, NULL) == -1) {
			perror("sigaction");
			exit(1);
		}

		/* 解除SIGCHLD次你好屏蔽 */
		if(sigprocmask(SIG_BLOCK, &old, NULL) == -1) {
			perror("sigprocmask");
			exit(1);
		}


		char path[64];
		getcwd(path, sizeof(path));
		printf("%s\n", path);
		/* 父进程向管道中写 */
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);


		if(execlp("ls", "ls", path, NULL) == -1) {
			perror("exec");
			exit(1);
		}
	}
	return 0;
}
