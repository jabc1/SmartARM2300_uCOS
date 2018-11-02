/****************************************Copyright (c) ****************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**�D�D�DFile Info�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D
**  File          name :main.h
**  Last modified Date :
**  Last       Version :V1.0
**  Descriptions       :�û�����������ͷ�ļ�
**
**�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D
** Created   	    by :
** Created  	  date :2007-4-17
** Version             :
** Descriptions        :
**
**�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D
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

//��һ������Ķ�
#include "config.h"

/**********************************************************************************
**  		   Ӧ�ó�������             
**		Application Program Configurations
**********************************************************************************/
//���¸�����Ҫ�Ķ�

#define     BUZZER                  1 << 27               // P1.27���Ʒ��������͵�ƽ����

#define     BUZZER_Set()            PINSEL3&=0xFFCFFFFF,IO1DIR|=(1<<27),IO1CLR|=(1<<27)  // ��������
#define     BUZZER_Clr()            IO1SET|=(1<<27) 

#ifdef __cplusplus
	}
#endif
#endif
/*******************************************************************************************
                              End Of File
*******************************************************************************************/
