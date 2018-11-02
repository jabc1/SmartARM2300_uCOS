/****************************************Copyright (c)**************************************************
**                               Guangzou ZLG-MCU Development Co.,LTD.
**                                      graduate school
**                                 http://www.zlgmcu.com
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			main.c
** Last modified Date:  2004-09-16
** Last Version:		1.0
** Descriptions:		The main() function example template
**
**------------------------------------------------------------------------------------------------------
** Created by:			Chenmingji
** Created date:		2004-09-16
** Version:				1.0
** Descriptions:		The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
********************************************************************************************************/
#include "main.h"

#define TASK0_ID            16      		// �����ID
#define TASK0_PRIO          TASK0_ID		// ��������ȼ�
#define TASK0_STACK_SIZE    256     		// �����û���ջ����   

#define TASK1_ID            17      		// �����ID
#define TASK1_PRIO          TASK1_ID		// ��������ȼ�
#define TASK1_STACK_SIZE    512     		// �����û���ջ����   
   
#define TASK2_ID            18				// �����ID
#define TASK2_PRIO          TASK2_ID		// ��������ȼ�
#define TASK2_STACK_SIZE    256				// �����û���ջ����

#define TASK3_ID            19				// �����ID
#define TASK3_PRIO          TASK3_ID		// ��������ȼ�
#define TASK3_STACK_SIZE    256				// �����û���ջ����

OS_STK  TASK0_STACK[TASK0_STACK_SIZE];
OS_STK  TASK1_STACK[TASK1_STACK_SIZE];
OS_STK  TASK2_STACK[TASK2_STACK_SIZE];
OS_STK  TASK3_STACK[TASK3_STACK_SIZE];

void TASK0(void *pdata);
void TASK1(void *pdata);
void TASK2(void *pdata);
void TASK3(void *pdata);

/*********************************************************************************************************
** Function name : main
** Descriptions  : ������
** Input         : �� 
** Output        : �� 
** Created Date  : 2006-04-11
********************************************************************************************************/
int main (void)
{
    OSInit(); 
    OSTaskCreateExt(TASK0,
                    (void *)0,
                    &TASK0_STACK[TASK0_STACK_SIZE-1],
                    TASK0_PRIO,
                    TASK0_ID,
                    &TASK0_STACK[0],
                    TASK0_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR); 
                              
    OSStart();                                       
}
		
/*******************************************************************************************
** Function name: TASK0
** Descriptions:  ��
** Input:         ��
** Output:        �� 
*******************************************************************************************/
void TASK0	(void *pdata)
{
	pdata = pdata;
#if OS_CRITICAL_METHOD == 3				// Allocate storage for CPU status register
    OS_CPU_SR  cpu_sr;
#endif	
    TargetInit();     
    
    BUZZER_Set();
	OSTimeDly(OS_TICKS_PER_SEC/10);
	BUZZER_Clr();
	OSTimeDly(OS_TICKS_PER_SEC/10);
	
	BUZZER_Set();
	OSTimeDly(OS_TICKS_PER_SEC/10);
	BUZZER_Clr();
	OSTimeDly(OS_TICKS_PER_SEC/5);
	
	OSTaskCreateExt(TASK1,
                    (void *)0,
                    &TASK1_STACK[TASK1_STACK_SIZE-1],
                    TASK1_PRIO,
                    TASK1_ID,
                    &TASK1_STACK[0],
                    TASK1_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  
     OSTaskCreateExt(TASK2,
                    (void *)0,
                    &TASK2_STACK[TASK2_STACK_SIZE-1],
                    TASK2_PRIO,
                    TASK2_ID,
                    &TASK2_STACK[0],
                    TASK2_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  
                     
    OSTaskCreateExt(TASK3,
                    (void *)0,
                    &TASK3_STACK[TASK3_STACK_SIZE-1],
                    TASK3_PRIO,
                    TASK3_ID,
                    &TASK3_STACK[0],
                    TASK3_STACK_SIZE,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  
   	while (1)
	{	
		OSTimeDly(OS_TICKS_PER_SEC);
	}
}
/*******************************************************************************************
** Function name: TASK1
** Descriptions:  ��
** Input:         ��
** Output:        �� 
*******************************************************************************************/
void TASK1	(void *pdata)
{
	pdata = pdata;	
	while(1)
	{		
		OSTimeDly(OS_TICKS_PER_SEC);		
	}	    
}
/*******************************************************************************************
** Function name: TASK2
** Descriptions:  ��
** Input:         ��
** Output:        �� 
*******************************************************************************************/
void TASK2	(void *pdata)
{
	pdata = pdata;	
	while(1)	
	{	
		OSTimeDly(OS_TICKS_PER_SEC);		
	}
}
/*******************************************************************************************
** Function name: TASK3
** Descriptions:  ��
** Input:         ��
** Output:        �� 
*******************************************************************************************/
void TASK3	(void *pdata)
{
	pdata = pdata;	
	while(1)	
	{			
		 BUZZER_Set();
	  	 OSTimeDly(OS_TICKS_PER_SEC/2);
		 BUZZER_Clr();		
		 OSTimeDly(OS_TICKS_PER_SEC/2);
	}
}


/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
