/*************************************************************************
    > File Name: client.h
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 09:16:32 2021
 ************************************************************************/

#include"common.h"


/* 登录函数 */
void login(int fd[2]); 

/* 退出函数 */
void quit();

/* 接收信息 */
void receive(int fd);

/* 发送消息 */
void send(int fd);
