/****************************************Copyright (c) ****************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**―――File Info――――――――――――――――――――――――――――――――――――――
**  File          name :main.c
**  Last modified Date :
**  Last       Version :V1.0
**  Descriptions       :用户中断程序
**
**―――――――――――――――――――――――――――――――――――――――――――――
** Created   	    by :
** Created  	  date :
** Version             :
** Descriptions        :
**
**―――――――――――――――――――――――――――――――――――――――――――――
** Modified	        by :
** Modified	      date :
** Version		       :
** Descriptions		   :
**
*******************************************************************************************/
#include "main.h"

/*******************************************************************************************
** 函数名称:void  FIQ_ISR(void)
** 函数功能:FIQ中断服务程序
** 入口参数:无
** 返 回 值:无
** 说    明:无
*******************************************************************************************/
void FIQ_Exception(void)
{
    /* 1.添加用户FIQ中断服务代码 */
	// 2.清除中断标志位
	//while(1);                                    // 修改为用户程序
	
    VICVectAddr = 0;           					 //interrupt close 通知中断控制器中断结束
}
/*******************************************************************************************
**                            End Of File
*******************************************************************************************/
