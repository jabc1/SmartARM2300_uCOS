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

//这一段无需改动
#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

typedef unsigned char  uint8;                   // 无符号8位整型变量  
typedef signed   char  int8;                    // 有符号8位整型变量  
typedef unsigned short uint16;                  // 无符号16位整型变量 
typedef signed   short int16;                   // 有符号16位整型变量 
typedef unsigned int   uint32;                  // 无符号32位整型变量 
typedef signed   int   int32;                   // 有符号32位整型变量 
typedef float          fp32;                    // 单精度浮点数（32位长度） 
typedef double         fp64;                    // 双精度浮点数（64位长度） 
#define GLOBAL	 extern	

/********************************
**      uC/OS-II的特殊代码      
********************************/
#define     USER_USING_MODE    0x10         	//  用户模式,ARM代码                 
                                             	//  只能是0x10,0x30,0x1f,0x3f之一      
#include "Includes.h"

/********************************
**      ARM的特殊代码                    
*********************************/
//这一段无需改动

#include    "LPC23xx.h"

/********************************
**     应用程序配置             
*********************************/
//以下根据需要改动
#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include    <stdlib.h>
#include    <setjmp.h>
#include    <rt_misc.h>
#include    "target.h"              		 	//这一句不能删除
#include    "VIC_Control.h"              		//这一句不能删除


/********************************
**     本例程的配置  
*********************************/

#define	USE_USB				1

#define Fosc                12000000			//	OSC = 12MHz

#if USE_USB	
	
	#define Fusbclk	48000000
	
	#define Fcclk	(Fosc * 4)					// 主频 Fcclk = 48MHz
	#define Fcco	(Fusbclk * (USBCLKDivValue+1))		// 如果用了USB,则Fcco是Fcclk与Fusbclk在275~550M之间的最小公倍数
														// Fcco是Fcclk在275~550M之间的最小倍数
	#define Fpclk	(Fcclk / 2)
	
	#define PLL_NValue			1
	#define PLL_MValue			(((Fcco/Fosc)*(PLL_NValue+1)/2)-1)
	#define CCLKDivValue		(Fcco/Fcclk-1)
	#define USBCLKDivValue		5	
#else
	#define Fcclk	(Fosc * 4)							// 主频 Fcclk = 48MHz
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
