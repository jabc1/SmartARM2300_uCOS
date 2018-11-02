/****************************************Copyright (c)**************************************************
**                               ������������Ƭ����չ���޹�˾
**                                     ��    ��    ��
**                                        ��Ʒһ�� 
**
**                                 http://www.zlgmcu.com
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: os_cpu_c.c
**��   ��   ��: ������
**����޸�����: 2004��8��27��
**��        ��: ��COS-II��lpc210x�ϵ���ֲ����C���Բ��֣����������ջ��ʼ������͹��Ӻ�����
**              ��ads1.2���룬����ʹ��ARM��ʽ����
**
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������: ������
** ��  ��: 1.0
** �ա���: 2003��6��5��
** �衡��: ԭʼ�汾
**
**------------------------------------------------------------------------------------------------------
** �޸���: ������
** ��  ��: 1.1
** �ա���: 2003��6��13��
** �衡��: ���Ӻ���IsrEnIRQ��ʹ����OSTaskStkInit��������
**
**------------------------------------------------------------------------------------------------------
** �޸���: ������
** ��  ��: 1.2
** �ա���: 2003��6��19��
** �衡��: �������жϷ�����
**
**------------------------------------------------------------------------------------------------------
** �޸���: ������
** ��  ��: 1.3
** �ա���: 2003��7��8��
** �衡��: ȥ������Ҫ�ĺ���IsrEnIRQ
**
**------------------------------------------------------------------------------------------------------
** �޸���: ������
** ��  ��: 1.4
** �ա���: 2004��8��27��
** �衡��: ���SWI�쳣�����Ч��
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���: 
** �ա���: 
** �衡��: 
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#define  OS_CPU_GLOBALS
#include "config.h"

#if OS_SELF_EN == 0 
int const _OSFunctionAddr[1] = {0};
int const _UsrFunctionAddr[1] = {0};
#endif

/*********************************************************************************************************
** ��������: OSTaskStkInit
** ��������: �����ջ��ʼ�����룬����������ʧ�ܻ�ʹϵͳ����
** �䡡��: task  : ����ʼִ�еĵ�ַ
**         pdata �����ݸ�����Ĳ���
**         ptos  ������Ķ�ջ��ʼλ��
**         opt   �����Ӳ�������ǰ�汾���ڱ��������ã���������μ�OSTaskCreateExt()��opt����
** �䡡��: ջ��ָ��λ��
** ȫ�ֱ���:
** ����ģ��: 
**
** ������: ������
** �ա���: 2003��6��5��
**-------------------------------------------------------------------------------------------------------
** �޸���: ������
** �ա���: 2003��6��13��
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/

        OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    OS_STK *stk;

    extern void TaskEntry(void);

    opt    = opt;                           /* 'opt'  û��ʹ�á������Ǳ������������    */
    stk    = ptos;                          /* ��ȡ��ջָ��                                       */

                                            /* �������񻷾���ADS1.2ʹ�����ݼ���ջ       */
    *stk = (OS_STK) TaskEntry;                   /*  pc  */
    *--stk = (OS_STK) task;                 /*  lr  */

    *--stk = 0;                             /*  r12  */
    *--stk = 0;                             /*  r11  */
    *--stk = 0;                             /*  r10  */
    *--stk = 0;                             /*  r9   */
    *--stk = 0;                             /*  r8   */
    *--stk = 0;                             /*  r7   */
    *--stk = 0;                             /*  r6   */
    *--stk = 0;                             /*  r5   */
    *--stk = 0;                             /*  r4   */
    *--stk = 0;                             /*  r3   */
    *--stk = 0;                             /*  r2   */
    *--stk = 0;                             /*  r1   */
    *--stk = (unsigned int) pdata;          /*  r0,��һ������ʹ��R0����   */
    *--stk = USER_USING_MODE;	                        /*  spsr������ IRQ, FIQ �ж�   */
    *--stk = 0;                             /*  ���жϼ�����OsEnterSum;    */

    return (stk);
}
/*********************************************************************************************************
** ��������: OSStartHighRdy
** ��������: uC/OS-II����ʱʹ��OSStartHighRdy���е�һ������,
**           ʵ���ǲ���swi 1ָ��
** �䡡��:   ��
** �䡡�� :  ��
** ȫ�ֱ���: ��
** ����ģ��: ��
** 
** ������: ������
** �ա���: 2003��6��5��
**-------------------------------------------------------------------------------------------------------
** �ޡ���: 
** �ա���: 
**-------------------------------------------------------------------------------------------------------
********************************************************************************************************/

        void OSStartHighRdy(void)
{
    _OSStartHighRdy();
}

/* ����ΪһЩ���Ӻ�����ȫ��Ϊ�պ���������˵���뿴������� */

#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookBegin (void)
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookEnd (void)
{
}
#endif


/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void)
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif


/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void)
{
}


/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION >= 251
void OSTaskIdleHook (void)
{
}
#endif
#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
