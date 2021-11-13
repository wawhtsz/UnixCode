/*************************************************************************
    > File Name: server.h
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 09:14:40 2021
 ************************************************************************/

#include"common.h"
/* 在线PID链表结构 */
struct onlinePID {
	struct onlinePID *pre;
	struct onlinePID *next;
	pid_t pid;
	int fd;
};












