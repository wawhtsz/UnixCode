#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
	//argv[0] ���ԭ�ļ���argv[1]���Ŀ���ļ�

	//���ļ�
	int fdsrc = open(argv[1], O_RDWR);
	if(fdsrc == -1) {
		perror("open srcfile faild");
		exit(1);
	}

	//��ȡ�ļ���С
	int count = lseek(fdsrc, 0, SEEK_END);
	printf("the srcfile size is %d\n",count);
	
	//��չ�ļ�
	int ret = lseek(fdsrc, 2000, SEEK_END);
	write(fdsrc, "end", 3);
	printf("after exetend the file's size is %d\n");

	close(fdsrc);
	return 0;
}
