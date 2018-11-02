/****************************************Copyright (c)**************************************************
**                               Guangzhou ZHIYUAN electronics Co.,LTD.
**                                     
**                                 http://www.embedtools.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			VIC_Control.h
** Last modified Date:  2007-07-09
** Last Version:		1.00
** Descriptions:		VIC_Control 软中断函数接口
**------------------------------------------------------------------------------------------------------
** Created by:			LinEnqiang
** Created date:		2007-07-06
** Version:				1.00
** Descriptions:		The original version
**------------------------------------------------------------------------------------------------------
** Modified by:			
** Modified date:		
** Version:				
** Descriptions:
********************************************************************************************************/
#ifndef _VIC_CONTROL_H_
#define _VIC_CONTROL_H_

#ifdef __cplusplus
extern "C" {
#endif

//----------------------IRQ配置信息结构体定义------------------//
typedef struct{
	uint32 Channel;
	uint32 PRI;
	uint32 ISRFunction;
	uint8  State;
}VIC_Config,*pVIC_Config;
//------------------------------------------------------------//

/*********************************************************************************************************
** Function name:			SetVICIRQ
** Descriptions:			设置所选外设的中断优先级、中断服务函数地址，并使能中断
** input parameters:		channel    	：外设对应的中断通道号
**							PRI       	：中断优先级
**							ISRFuction 	：中断服务函数地址

** Returned value:			成功		：返回 1
**							失败		：返回 0
*********************************************************************************************************/
__inline uint32 SetVICIRQ(uint32 channel,uint32 PRI,uint32 ISRFuction)
{
	return(OsSwiHandle4(0x100,channel,PRI,ISRFuction));	
} 
   
/*********************************************************************************************************
** Function name:			FreeVICIRQ
** Descriptions:			释放所选外设的IRQ资源
** input parameters:		channel    	：外设对应的中断通道号
** Returned value:			成功		：返回 1
**							失败		：返回 0
*********************************************************************************************************/
__inline uint32 FreeVICIRQ(uint32 channel)
{
	return(OsSwiHandle2(0x101,channel));
}

/*********************************************************************************************************
** Function name:			ReEnableVICIRQ
** Descriptions:			重新使能相应外设的中断
** input parameters:		channel    	：外设对应的中断通道号
** Returned value:			成功		：返回 1
**							失败		：返回 0
*********************************************************************************************************/
__inline uint32 ReEnableVICIRQ(uint32 channel)
{
	return(OsSwiHandle2(0x102,channel));
}

/*********************************************************************************************************
** Function name:			DisableVICIRQ
** Descriptions:			禁止相应外设的中断
** input parameters:		channel    	：外设对应的中断通道号
** Returned value:			成功		：返回 1
**							失败		：返回 0
*********************************************************************************************************/
__inline uint32 DisableVICIRQ(uint32 channel)
{
	return(OsSwiHandle2(0x103,channel));
}

/*********************************************************************************************************
** Function name:			GetVICIRQState
** Descriptions:			获取所选外设的中断通道号、优先级、中断服务函数地址及中断使能状态
** input parameters:		channel    	：外设对应的中断通道号
**							pISRConfig 	：IRQ配置信息结构体指针
** Returned value:			成功		：返回 1
**							失败		：返回 0
*********************************************************************************************************/
__inline uint32 GetVICIRQState(uint32 channel,pVIC_Config pISRConfig)
{
	return(OsSwiHandle3(0x104,channel,(int)pISRConfig));
}

/*********************************************************************************************************
** Function name:			SetVICFIQ
** Descriptions:			设置并使能所选中断通道号为FIQ中断
** input parameters:		channel    	：外设对应的中断通道号
** Returned value:			成功		：返回 1
**							失败		：返回 0
*********************************************************************************************************/
__inline uint32 SetVICFIQ(uint32 channel)
{
	return(OsSwiHandle2(0x105,channel));
}  
  
/*********************************************************************************************************
** Function name:			FreeVICFIQ
** Descriptions:			释放所选中断通道号的FIQ中断
** input parameters:		channel    	：外设对应的中断通道号
** Returned value:			成功		：返回 1
**							失败		：返回 0
*********************************************************************************************************/
__inline uint32 FreeVICFIQ(uint32 channel)
{
	return(OsSwiHandle2(0x106,channel));
}
//----------------------允许中断嵌套宏定义------------------//

#define		OS_ENABLE_NESTING		OS_EXIT_CRITICAL
#define		OS_DISABLE_NESTING		OS_ENTER_CRITICAL

//---------------------------------------------------------//
#ifdef __cplusplus
	}
#endif
#endif
