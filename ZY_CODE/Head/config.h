/****************************************Copyright (c)**************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**--------------File Info-------------------------------------------------------------------------------
** File Name			: config.h
** Last modified Date	: 2004-09-17
** Last Version			: V1.00
** Descriptions			: User Configurable File
**
**------------------------------------------------------------------------------------------------------
** Created By			: Chenmingji
** Created date			: 2004-09-17
** Version				: V1.00
** Descriptions			: First version
**
**------------------------------------------------------------------------------------------------------
** Modified by			: LinEnqiang
** Modified date		: 2007-05-15
** Version				: V1.01
** Descriptions			: Modified for LPC23xx
**
********************************************************************************************************/
#ifndef __CONFIG_H 
#define __CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

//��һ������Ķ�
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char  uint8;                   // �޷���8λ���ͱ���  
typedef signed   char  int8;                    // �з���8λ���ͱ���  
typedef unsigned short uint16;                  // �޷���16λ���ͱ��� 
typedef signed   short int16;                   // �з���16λ���ͱ��� 
typedef unsigned int   uint32;                  // �޷���32λ���ͱ��� 
typedef signed   int   int32;                   // �з���32λ���ͱ��� 
typedef float          fp32;                    // �����ȸ�������32λ���ȣ� 
typedef double         fp64;                    // ˫���ȸ�������64λ���ȣ� 
#define GLOBAL	 extern	

/********************************
**      uC/OS-II���������      
********************************/
#define     USER_USING_MODE    0x10         	//  �û�ģʽ,ARM����                 
                                             	//  ֻ����0x10,0x30,0x1f,0x3f֮һ      
#include "Includes.h"

/********************************
**      ARM���������                    
*********************************/
//��һ������Ķ�

#include    "LPC23xx.h"

/********************************
**     Ӧ�ó�������             
*********************************/
//���¸�����Ҫ�Ķ�
#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <setjmp.h>
#include    <rt_misc.h>
#include    "target.h"              		 	//��һ�䲻��ɾ��
#include    "VIC_Control.h"              		//��һ�䲻��ɾ��


/********************************
**     �����̵�����  
*********************************/

#define	USE_USB				1

#define Fosc                12000000			//	OSC = 12MHz

#if USE_USB	
	
	#define Fusbclk	48000000
	
	#define Fcclk	(Fosc * 4)					// ��Ƶ Fcclk = 48MHz
	#define Fcco	(Fusbclk * (USBCLKDivValue+1))		// �������USB,��Fcco��Fcclk��Fusbclk��275~550M֮�����С������
														// Fcco��Fcclk��275~550M֮�����С����
	#define Fpclk	(Fcclk / 2)
	
	#define PLL_NValue			1
	#define PLL_MValue			(((Fcco/Fosc)*(PLL_NValue+1)/2)-1)
	#define CCLKDivValue		(Fcco/Fcclk-1)
	#define USBCLKDivValue		5	
#else
	#define Fcclk	(Fosc * 4)							// ��Ƶ Fcclk = 48MHz
	#define Fcco    (Fcclk* 6)
	
	#define Fpclk	(Fcclk / 4)
	
	#define PLL_NValue			1	
	#define PLL_MValue			(((Fcco/Fosc)*(PLL_NValue+1)/2)-1)
	#define CCLKDivValue		(Fcco/Fcclk-1)
	#define USBCLKDivValue		254		
#endif	

#ifdef __cplusplus
	}
#endif

#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
