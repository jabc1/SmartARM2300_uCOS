/****************************************Copyright (c)**************************************************
**                               Guangzhou ZHIYUAN electronics Co.,LTD.
**                                     
**                                 http://www.embedtools.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			VIC_Control.h
** Last modified Date:  2007-07-09
** Last Version:		1.00
** Descriptions:		VIC_Control ���жϺ����ӿ�
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

//----------------------IRQ������Ϣ�ṹ�嶨��------------------//
typedef struct{
	uint32 Channel;
	uint32 PRI;
	uint32 ISRFunction;
	uint8  State;
}VIC_Config,*pVIC_Config;
//------------------------------------------------------------//

/*********************************************************************************************************
** Function name:			SetVICIRQ
** Descriptions:			������ѡ������ж����ȼ����жϷ�������ַ����ʹ���ж�
** input parameters:		channel    	�������Ӧ���ж�ͨ����
**							PRI       	���ж����ȼ�
**							ISRFuction 	���жϷ�������ַ

** Returned value:			�ɹ�		������ 1
**							ʧ��		������ 0
*********************************************************************************************************/
__inline uint32 SetVICIRQ(uint32 channel,uint32 PRI,uint32 ISRFuction)
{
	return(OsSwiHandle4(0x100,channel,PRI,ISRFuction));	
} 
   
/*********************************************************************************************************
** Function name:			FreeVICIRQ
** Descriptions:			�ͷ���ѡ�����IRQ��Դ
** input parameters:		channel    	�������Ӧ���ж�ͨ����
** Returned value:			�ɹ�		������ 1
**							ʧ��		������ 0
*********************************************************************************************************/
__inline uint32 FreeVICIRQ(uint32 channel)
{
	return(OsSwiHandle2(0x101,channel));
}

/*********************************************************************************************************
** Function name:			ReEnableVICIRQ
** Descriptions:			����ʹ����Ӧ������ж�
** input parameters:		channel    	�������Ӧ���ж�ͨ����
** Returned value:			�ɹ�		������ 1
**							ʧ��		������ 0
*********************************************************************************************************/
__inline uint32 ReEnableVICIRQ(uint32 channel)
{
	return(OsSwiHandle2(0x102,channel));
}

/*********************************************************************************************************
** Function name:			DisableVICIRQ
** Descriptions:			��ֹ��Ӧ������ж�
** input parameters:		channel    	�������Ӧ���ж�ͨ����
** Returned value:			�ɹ�		������ 1
**							ʧ��		������ 0
*********************************************************************************************************/
__inline uint32 DisableVICIRQ(uint32 channel)
{
	return(OsSwiHandle2(0x103,channel));
}

/*********************************************************************************************************
** Function name:			GetVICIRQState
** Descriptions:			��ȡ��ѡ������ж�ͨ���š����ȼ����жϷ�������ַ���ж�ʹ��״̬
** input parameters:		channel    	�������Ӧ���ж�ͨ����
**							pISRConfig 	��IRQ������Ϣ�ṹ��ָ��
** Returned value:			�ɹ�		������ 1
**							ʧ��		������ 0
*********************************************************************************************************/
__inline uint32 GetVICIRQState(uint32 channel,pVIC_Config pISRConfig)
{
	return(OsSwiHandle3(0x104,channel,(int)pISRConfig));
}

/*********************************************************************************************************
** Function name:			SetVICFIQ
** Descriptions:			���ò�ʹ����ѡ�ж�ͨ����ΪFIQ�ж�
** input parameters:		channel    	�������Ӧ���ж�ͨ����
** Returned value:			�ɹ�		������ 1
**							ʧ��		������ 0
*********************************************************************************************************/
__inline uint32 SetVICFIQ(uint32 channel)
{
	return(OsSwiHandle2(0x105,channel));
}  
  
/*********************************************************************************************************
** Function name:			FreeVICFIQ
** Descriptions:			�ͷ���ѡ�ж�ͨ���ŵ�FIQ�ж�
** input parameters:		channel    	�������Ӧ���ж�ͨ����
** Returned value:			�ɹ�		������ 1
**							ʧ��		������ 0
*********************************************************************************************************/
__inline uint32 FreeVICFIQ(uint32 channel)
{
	return(OsSwiHandle2(0x106,channel));
}
//----------------------�����ж�Ƕ�׺궨��------------------//

#define		OS_ENABLE_NESTING		OS_EXIT_CRITICAL
#define		OS_DISABLE_NESTING		OS_ENTER_CRITICAL

//---------------------------------------------------------//
#ifdef __cplusplus
	}
#endif
#endif
