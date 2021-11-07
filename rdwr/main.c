//������ʵ�ִ�src.txt �ж�ȡ�������������  dst.txt ��
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {
	int fdsrc = 0; //�ļ�������
	int fddst = 0;

	char buf[30]; //������
	
	char srcfile[30];//ԭ�ļ�����
	char dstfile[30];//Ŀ���ļ�����
	

	printf("Please insert the source file name:");
	scanf("%s", srcfile);
	printf("Please insert the dst file name:");
	scanf("%s", dstfile);

	//���ļ�
	fdsrc = open(srcfile, O_RDONLY);
	if(fdsrc == -1) {
		perror("open file faild");
		exit(1);
	}
	fddst = open(dstfile, O_WRONLY | O_TRUNC);
	if(fddst == -1) {
		perror("open dstfile faild");
		exit(1);
	}
	//��ȡ�ļ�����
	
	int count = 0;//ͳ�ƶ������ַ�
	while(count = read(fdsrc, buf, sizeof(buf)) > 0) {
		if(write(fddst, buf, count) == -1) {
			perror("write file faild");
			exit(1);
		}
	}
	//�ر��ļ�
	if(close(fdsrc) == -1) {
		perror("close srcfile faild");
		exit(1);
	}
	if(close(fddst) == -1) {
		perror("close dstfile faild");
		exit(1);
	}	
	return 0;	
}
