/****************************************Copyright (c) ****************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**
**�D�D�DFile Info�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D
**  File          name :main.c
**  Last modified Date :
**  Last       Version :V1.0
**  Descriptions       :�û��жϳ���
**
**�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D�D
** Created   	    by :
** Created  	  date :
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
#include "main.h"

/*******************************************************************************************
** ��������:void  FIQ_ISR(void)
** ��������:FIQ�жϷ������
** ��ڲ���:��
** �� �� ֵ:��
** ˵    ��:��
*******************************************************************************************/
void FIQ_Exception(void)
{
    /* 1.����û�FIQ�жϷ������ */
	// 2.����жϱ�־λ
	//while(1);                                    // �޸�Ϊ�û�����
	
    VICVectAddr = 0;           					 //interrupt close ֪ͨ�жϿ������жϽ���
}
/*******************************************************************************************
**                            End Of File
*******************************************************************************************/
