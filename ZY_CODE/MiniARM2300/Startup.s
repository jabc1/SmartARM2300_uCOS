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
;定义堆栈的大小
SVC_STACK_LEGTH         EQU         0
FIQ_STACK_LEGTH         EQU         0
IRQ_STACK_LEGTH         EQU         9*8             ;every layer need 9 bytes stack , permit 8 layer .每层嵌套需要9个字堆栈，允许8层嵌套
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
;引入的外部标号在这声明
    IMPORT  FIQ_Exception                   ;Fast interrupt exceptions handler 快速中断异常处理程序
    IMPORT  __main                          ;The entry point to the main function C语言主程序入口 
    IMPORT  TargetResetInit                 ;initialize the target board 目标板基本初始化
    IMPORT __use_no_semihosting_swi
    IMPORT __use_two_region_memory
    IMPORT	SoftwareInterrupt
    IMPORT  RunFirst
    IMPORT  VICControl
    
;The emported labels    
;给外部使用的标号在这声明
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
;中断向量表
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
        
;IRQ中断
    MACRO
    ISR
; 调用c语言的中断处理程序
        LDR     R2, =VICVectAddr
        LDR     R3, [R2]
        MOV     LR, PC
        BX      R3
    MEND
    INCLUDE		irq.inc			; Inport the head file 引入头文件

IRQ_Handler  HANDLER

	
;快速中断
FIQ_Handler
        STMFD   SP!, {R0-R3, LR}
        BL      FIQ_Exception
        LDMFD   SP!, {R0-R3, LR}
        SUBS    PC,  LR,  #4            
;/*********************************************************************************************************
;** unction name 	函数名称: 	ResetInit
;** Descriptions 	功能描述: 	RESET  复位入口
;** input parameters 	输　入:   	None 无
;** Returned value   	输　出 :  	None 无
;** Used global variables 全局变量: 	None 无
;** Calling modules 	调用模块: 	None 无
;** 
;** Created by 		作　者: 	Chenmingji 陈明计
;** Created Date 	日　期: 	2004/02/02 2004年2月2日
;**-------------------------------------------------------------------------------------------------------
;** Modified by 	修　改: Chenmingji 陈明计
;** Modified date 	日　期: 2004/02/02 2004年3月3日
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
ResetInit    
        BL      RunFirst
        BL      InitStack               ; Initialize the stack 初始化堆栈
        BL      TargetResetInit         ; Initialize the target board 目标板基本初始化
                                        ; Jump to the entry point of C program 跳转到c语言入口       
        B       __main

;/*********************************************************************************************************
;** unction name 	函数名称: 	InitStack
;** Descriptions 	功能描述: 	Initialize the stacks  初始化堆栈
;** input parameters 	输　入:   	None 无
;** Returned value   	输　出 :  	None 无
;** Used global variables 全局变量: 	None 无
;** Calling modules 	调用模块: 	None 无
;** 
;** Created by 		作　者: 	Chenmingji 陈明计
;** Created Date 	日　期: 	2004/02/02 2004年2月2日
;**-------------------------------------------------------------------------------------------------------
;** Modified by 	修　改: 
;** Modified date 	日　期: 
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
InitStack    
        MOV     R0, LR                
;Build the SVC stack
;设置管理模式堆栈
        MSR     CPSR_c, #0xd3		
        LDR     SP, StackSvc
;Build the IRQ stack
;设置中断模式堆栈
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq
;Build the FIQ stack	
;设置快速中断模式堆栈
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq
;Build the DATAABORT stack
;设置中止模式堆栈
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt
;Build the UDF stack
;设置未定义模式堆栈
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd
;Build the SYS stack
;设置系统模式堆栈
        MSR     CPSR_c, #0xd0
        LDR     SP, =StackUsr              
        MOV     PC, R0
;/*********************************************************************************************************
;** unction name 	函数名称: 	__user_initial_stackheap
;** Descriptions 	功能描述: 	Initial the function library stacks and heaps, can not deleted!   库函数初始化堆和栈，不能删除
;** input parameters 	输　入:   	reference by function library 参考库函数手册
;** Returned value   	输　出 :  	reference by function library 参考库函数手册
;** Used global variables 全局变量: 	None 无
;** Calling modules 	调用模块: 	None 无
;** 
;** Created by 		作　者: 	Chenmingji 陈明计
;** Created Date 	日　期: 	2004/02/02 2004年2月2日
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
;** unction name 	函数名称: 	CrpData
;** Descriptions 	功能描述: 	encrypt the chip
;** input parameters 	输　入:   	None 无
;** Returned value   	输　出 :  	None 无
;** Used global variables 全局变量: 	None 无
;** Calling modules 	调用模块: 	None 无
;** 
;** Created by 		作　者: 	Chenmingji 陈明计
;** Created Date 	日　期: 	2004/03/27 2004年3月27日
;**-------------------------------------------------------------------------------------------------------
;** Modified by 	修　改: 
;** Modified date 	日　期: 
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
    DCD     0x87654321          ;/*When the Data is 0x87654321,user code be not protected. 当此数为0x87654321时，用户程序被保护 */
    ELSE
    DCD     0xffffffff          ;/*When the Data is 0xffffffff,user code be not protected. 当此数为0xffffffff时，用户程序不被保护 */
    ENDIF
;------------------------------------------------------------------------------------------------


;/* 分配堆栈空间 */    
        
        AREA    MyStacks, DATA, NOINIT, ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4  ;Stack spaces for Administration Mode 管理模式堆栈空间
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  ;Stack spaces for Interrupt ReQuest Mode 中断模式堆栈空间
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  ;Stack spaces for Fast Interrupt reQuest Mode 快速中断模式堆栈空间
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  ;Stack spaces for Suspend Mode 中止义模式堆栈空间
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4  ;Stack spaces for Undefined Mode 未定义模式堆栈

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
