#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
	int fd;
	//���Ѿ����ڵ��ļ�
	fd = open("wenjian.txt", O_RDWR);
	if(fd == -1) {
		perror("open file");
		exit(1);
	}
	//�ر��ļ�
	int ret = close(fd);
	printf("ret = %d\n", ret);

	//�������ļ�
	fd = open("newfile.txt", O_CREAT | O_RDWR, 777);
	if(fd == -1) {
		perror("create file");
		exit(1);
	}
	ret = close(fd);
	if(ret == 0)
		printf("close file %d succeed\n", fd);
	//�ر��ļ�
	ret = close(fd);
	printf("ret = %d\n", ret);
	//���ļ��ض�
	fd = open("wenjian.txt", O_RDWR | O_TRUNC);
	if(fd == -1) {
		perror("open file");
		exit(1);
	}

	
	return 0;
}
