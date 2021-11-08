/*************************************************************************
    > File Name: main.c
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Mon Nov  8 20:44:35 2021
 ************************************************************************/

#include<stdio.h>
#include<dirent.h>
#include<sys/types.h>
#include<stdlib.h>


int getFileNum(char *root) {
	//open dir
	DIR *dir = NULL;
	dir = opendir(root);
	if(dir == NULL ) {
		perror("open dir faild");
		exit(1);
	}

	int total = 0;
	//遍历打开当前目录
	char path[1024] = {0};
	struct dirent *pd = NULL;	
	while((pd = readdir(dir)) != NULL) {
		//过滤掉 . .. 目录
		if(strcmp(pd->d_name, ".") == 0 ||  strcmp(pd->d_name, "..") == 0) {
			continue;
		}
		//如果是目录，递归进入
		if(pd -> d_type == DT_DIR) {
			sprintf(path, "%s/%s", root, pd->d_name);
			total += getFileNum(path);
		} else if (pd->d_type == DT_REG) { //如果是普通文件
			total += 1;
		}
	}
	close(dir);
	return total;
}
int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("/a.out dir");
		exit(1);
	}

	int total = 0;
	total = getFileNum(argv[1]);
	printf("%s has %d files\n", argv[1], total);
	return 0;

}
