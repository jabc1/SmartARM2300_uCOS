;/****************************************Copyright (c)**************************************************
;**                               Guangzou ZLG-MCU Development Co.,LTD.
;**                                      graduate school
;**                                 http://www.zlgmcu.com
;**
;**--------------File Info-------------------------------------------------------------------------------
;** File name: 			Startup.s
;** Last modified Date:  2004-09-17
;** Last Version: 		1.0
;** Descriptions: 		The start up codes for LPC2100, including the initializing codes for the entry point of exceptions and the stacks of user tasks.
;**				Every project should have a independent copy of this file for related modifications
;**------------------------------------------------------------------------------------------------------
;** Created by: 			Chenmingji
;** Created date:   		2004-02-02
;** Version:			1.0
;** Descriptions: 		The original version
;**
;**------------------------------------------------------------------------------------------------------
;** Modified by: 		Chenmingji
;** Modified date:		2004-09-17
;** Version:			1.01
;** Descriptions: 		Modified the bus setting to adapt for many common situations 
;**
;**------------------------------------------------------------------------------------------------------
;** Modified by: 		Chenmingji
;** Modified date:		2004-09-17
;** Version:			1.02
;** Descriptions: 		Added codes to support the enciphering of the chip
;**
;**------------------------------------------------------------------------------------------------------
;** Modified by: 		Chenmingji
;** Modified date:		2004-09-17
;** Version:			1.04
;** Descriptions: 		Renewed the template, added codes to support more compilers 
;**
;**------------------------------------------------------------------------------------------------------
;** Modified by: 		LinEnqiang
;** Modified date:		2007-07-01	
;** Version:			1.05
;** Descriptions: 		For MiniARM2300
;**------------------------------------------------------------------------------------------------------
;** Modified by: 		LinEnqiang
;** Modified date:		2007-10-25	
;** Version:			1.06
;** Descriptions: 		For MiniARM2300
;**
;********************************************************************************************************/
;define the stack size
;�����ջ�Ĵ�С
SVC_STACK_LEGTH         EQU         0
FIQ_STACK_LEGTH         EQU         0
IRQ_STACK_LEGTH         EQU         9*8             ;every layer need 9 bytes stack , permit 8 layer .ÿ��Ƕ����Ҫ9���ֶ�ջ������8��Ƕ��
ABT_STACK_LEGTH         EQU         0
UND_STACK_LEGTH         EQU         0

NoInt       EQU 0x80
NoFIQ		EQU	0x40

USR32Mode   EQU 0x10
SVC32Mode   EQU 0x13
SYS32Mode   EQU 0x1f
IRQ32Mode   EQU 0x12
FIQ32Mode   EQU 0x11

VICVectAddr0  EQU 0xfffff100
VICVectAddr   EQU 0xffffff00
VICVectPri0   EQU 0xfffff200
VICIntEnable  EQU 0xfffff010
VICIntEnClr   EQU 0xfffff014
VICIntSelect  EQU 0xfffff00c
VICProtection EQU 0xFFFFF020 

;The imported labels    
;������ⲿ�����������
    IMPORT  FIQ_Exception                   ;Fast interrupt exceptions handler �����ж��쳣�������
    IMPORT  __main                          ;The entry point to the main function C������������� 
    IMPORT  TargetResetInit                 ;initialize the target board Ŀ��������ʼ��
    IMPORT __use_no_semihosting_swi
    IMPORT __use_two_region_memory
    IMPORT	SoftwareInterrupt
    IMPORT  RunFirst
    IMPORT  VICControl
    
;The emported labels    
;���ⲿʹ�õı����������
    EXPORT  Reset    
	EXPORT  StackUsr
   
	EXPORT  InitStack
	EXPORT  bottom_of_heap   
	EXPORT  __user_initial_stackheap
	
    CODE32
	PRESERVE8

    AREA    vectors,CODE,READONLY
        ENTRY

;interrupt vectors
;�ж�������
;RunFirst
Reset
        LDR     	PC, ResetAddr
        LDR     	PC, UndefinedAddrA
        LDR    	 	PC, SWI_Addr
        LDR     	PC, PrefetchAddrA
        LDR     	PC, DataAbortAddrA
        DCD     	0xB8A06F58
        LDR     	PC, IRQ_Addr
        LDR     	PC, FIQ_Addr

ResetAddr           DCD     ResetInit
UndefinedAddrA      DCD     Undefined
SWI_Addr            DCD     SoftwareInterruptAdd
PrefetchAddrA       DCD     PrefetchAbort
DataAbortAddrA      DCD     DataAbort
Nouse               DCD     0
IRQ_Addr            DCD     IRQ_Handler
FIQ_Addr            DCD     FIQ_Handler

Undefined
        B       .
PrefetchAbort
        B       .
DataAbort
        B       . 

SoftwareInterruptAdd 
        CMP     R0, #0x100
        BLO     SoftwareInterrupt
        B       VICControl    
        
;IRQ�ж�
    MACRO
    ISR
; ����c���Ե��жϴ������
        LDR     R2, =VICVectAddr
        LDR     R3, [R2]
        MOV     LR, PC
        BX      R3
    MEND
    INCLUDE		irq.inc			; Inport the head file ����ͷ�ļ�

IRQ_Handler  HANDLER

	
;�����ж�
FIQ_Handler
        STMFD   SP!, {R0-R3, LR}
        BL      FIQ_Exception
        LDMFD   SP!, {R0-R3, LR}
        SUBS    PC,  LR,  #4            
;/*********************************************************************************************************
;** unction name 	��������: 	ResetInit
;** Descriptions 	��������: 	RESET  ��λ���
;** input parameters 	�䡡��:   	None ��
;** Returned value   	�䡡�� :  	None ��
;** Used global variables ȫ�ֱ���: 	None ��
;** Calling modules 	����ģ��: 	None ��
;** 
;** Created by 		������: 	Chenmingji ������
;** Created Date 	�ա���: 	2004/02/02 2004��2��2��
;**-------------------------------------------------------------------------------------------------------
;** Modified by 	�ޡ���: Chenmingji ������
;** Modified date 	�ա���: 2004/02/02 2004��3��3��
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
ResetInit    
        BL      RunFirst
        BL      InitStack               ; Initialize the stack ��ʼ����ջ
        BL      TargetResetInit         ; Initialize the target board Ŀ��������ʼ��
                                        ; Jump to the entry point of C program ��ת��c�������       
        B       __main

;/*********************************************************************************************************
;** unction name 	��������: 	InitStack
;** Descriptions 	��������: 	Initialize the stacks  ��ʼ����ջ
;** input parameters 	�䡡��:   	None ��
;** Returned value   	�䡡�� :  	None ��
;** Used global variables ȫ�ֱ���: 	None ��
;** Calling modules 	����ģ��: 	None ��
;** 
;** Created by 		������: 	Chenmingji ������
;** Created Date 	�ա���: 	2004/02/02 2004��2��2��
;**-------------------------------------------------------------------------------------------------------
;** Modified by 	�ޡ���: 
;** Modified date 	�ա���: 
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
InitStack    
        MOV     R0, LR                
;Build the SVC stack
;���ù���ģʽ��ջ
        MSR     CPSR_c, #0xd3		
        LDR     SP, StackSvc
;Build the IRQ stack
;�����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq
;Build the FIQ stack	
;���ÿ����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq
;Build the DATAABORT stack
;������ֹģʽ��ջ
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt
;Build the UDF stack
;����δ����ģʽ��ջ
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd
;Build the SYS stack
;����ϵͳģʽ��ջ
        MSR     CPSR_c, #0xd0
        LDR     SP, =StackUsr              
        MOV     PC, R0
;/*********************************************************************************************************
;** unction name 	��������: 	__user_initial_stackheap
;** Descriptions 	��������: 	Initial the function library stacks and heaps, can not deleted!   �⺯����ʼ���Ѻ�ջ������ɾ��
;** input parameters 	�䡡��:   	reference by function library �ο��⺯���ֲ�
;** Returned value   	�䡡�� :  	reference by function library �ο��⺯���ֲ�
;** Used global variables ȫ�ֱ���: 	None ��
;** Calling modules 	����ģ��: 	None ��
;** 
;** Created by 		������: 	Chenmingji ������
;** Created Date 	�ա���: 	2004/02/02 2004��2��2��
;**-------------------------------------------------------------------------------------------------------
;** Modified by 	
;** Modified date 	
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
__user_initial_stackheap    
    LDR   R0, =bottom_of_heap		
;    LDR   R1, =StackUsr			
    LDR   R2, =top_of_heap		
    LDR   R3, =bottom_of_Stacks		
    MOV   PC, LR
		
   LTORG 	
StackSvc           DCD     SvcStackSpace + (SVC_STACK_LEGTH - 1)* 4
StackIrq           DCD     IrqStackSpace + (IRQ_STACK_LEGTH - 1)* 4
StackFiq           DCD     FiqStackSpace + (FIQ_STACK_LEGTH - 1)* 4
StackAbt           DCD     AbtStackSpace + (ABT_STACK_LEGTH - 1)* 4
StackUnd           DCD     UndtStackSpace + (UND_STACK_LEGTH - 1)* 4

    EXPORT _sys_exit
_sys_exit
    B       .


    EXPORT __rt_div0
    EXPORT fputc
    EXPORT fgetc
    EXPORT _sys_close
    EXPORT _sys_write
    EXPORT _sys_read
;    EXPORT _ttywrch
    EXPORT _sys_istty
    EXPORT _sys_seek
    EXPORT _sys_ensure
    EXPORT _sys_flen
    EXPORT _sys_tmpnam
    EXPORT _sys_command_string

__rt_div0
fputc
fgetc
_sys_close
_sys_write
_sys_read
;_ttywrch
_sys_istty
_sys_seek
_sys_ensure
_sys_flen
_sys_tmpnam
_sys_command_string    	
    MOV     R0, #0
    MOV     PC, LR
       
;/*********************************************************************************************************
;** unction name 	��������: 	CrpData
;** Descriptions 	��������: 	encrypt the chip
;** input parameters 	�䡡��:   	None ��
;** Returned value   	�䡡�� :  	None ��
;** Used global variables ȫ�ֱ���: 	None ��
;** Calling modules 	����ģ��: 	None ��
;** 
;** Created by 		������: 	Chenmingji ������
;** Created Date 	�ա���: 	2004/03/27 2004��3��27��
;**-------------------------------------------------------------------------------------------------------
;** Modified by 	�ޡ���: 
;** Modified date 	�ա���: 
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
   IF  . >= 0x1fc
        IF :DEF: EN_CRP
            INFO    1,"\nThe data at 0x000001fc must be 0x87654321.\nPlease delete some source before this line."
        ELSE
            INFO    1,"\nThe data at 0x000001fc must be 0xffffffff.\nPlease delete some source before this line."
        ENDIF
   ENDIF

CrpData
    WHILE . < 0x1fc
    NOP
    WEND

CrpData1
    IF :DEF: EN_CRP
    DCD     0x87654321          ;/*When the Data is 0x87654321,user code be not protected. ������Ϊ0x87654321ʱ���û����򱻱��� */
    ELSE
    DCD     0xffffffff          ;/*When the Data is 0xffffffff,user code be not protected. ������Ϊ0xffffffffʱ���û����򲻱����� */
    ENDIF
;------------------------------------------------------------------------------------------------


;/* �����ջ�ռ� */    
        
        AREA    MyStacks, DATA, NOINIT, ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4  ;Stack spaces for Administration Mode ����ģʽ��ջ�ռ�
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  ;Stack spaces for Interrupt ReQuest Mode �ж�ģʽ��ջ�ռ�
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  ;Stack spaces for Fast Interrupt reQuest Mode �����ж�ģʽ��ջ�ռ�
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  ;Stack spaces for Suspend Mode ��ֹ��ģʽ��ջ�ռ�
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4  ;Stack spaces for Undefined Mode δ����ģʽ��ջ

        AREA    Heap, DATA, NOINIT
bottom_of_heap    SPACE   1

        AREA    StackBottom, DATA, NOINIT
bottom_of_Stacks    SPACE   1

        AREA    HeapTop, DATA, NOINIT
top_of_heap

        AREA    Stacks, DATA, NOINIT
StackUsr  
    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
