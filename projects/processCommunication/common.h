/*************************************************************************
    > File Name: common.h
    > Author:wxl_ouc
    > Mail: wxl_ouc@qq.com
    > Created Time: Sat Nov 13 09:26:02 2021
 ************************************************************************/

#include<sys/types.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>


#define COMMON_FIFO "./commonFIFO"
#define BUF_SIZE   30 

/* mseeage type */
#define SYN 0    //请求登录
#define MSG 1    //发送数据
#define FIN 2    //退出登录

#define SYN_DST_PID 3 //用于登录目的PID
#define FIN_DST_PID 3 //用于退出登录目的PID

/* 消息结构 */
struct msg {
	int type;
	int srcPID;
	int dstPID;
	char data[BUF_SIZE];
};

/* 打包消息 */
void create_msg(int type, int dstPID, char data[], struct msg *message);

/* 
 * 功能：创建并打开用户专用fifo 
 * 返回值：成功返回fd
 *
 */
int create_special_fifo (int srcPID, int is_server);


/* 
 * 功能：并打开公用fifo 
 * 返回值：成功返回fd
 *
 */
int open_common_fifo (int is_read);





















