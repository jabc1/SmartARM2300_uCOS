/****************************************Copyright (c) ****************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**―――File Info――――――――――――――――――――――――――――――――――――――
**  File          name :main.h
**  Last modified Date :
**  Last       Version :V1.0
**  Descriptions       :用户程序主函数头文件
**
**―――――――――――――――――――――――――――――――――――――――――――――
** Created   	    by :
** Created  	  date :2007-4-17
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
#ifndef __MAIN_H 
#define __MAIN_H

#ifdef __cplusplus

extern "C" {
#endif

//这一段无需改动
#include "config.h"

/**********************************************************************************
**  		   应用程序配置             
**		Application Program Configurations
**********************************************************************************/
//以下根据需要改动

#define     BUZZER                  1 << 27               // P1.27控制蜂鸣器，低电平蜂鸣

#define     BUZZER_Set()            PINSEL3&=0xFFCFFFFF,IO1DIR|=(1<<27),IO1CLR|=(1<<27)  // 开蜂鸣器
#define     BUZZER_Clr()            IO1SET|=(1<<27) 

#ifdef __cplusplus
	}
#endif
#endif
/*******************************************************************************************
                              End Of File
*******************************************************************************************/
