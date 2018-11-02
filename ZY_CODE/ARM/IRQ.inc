;/****************************************Copyright (c)**************************************************
;**                               广州周立功单片机发展有限公司
;**                                     研    究    所
;**                                        产品一部 
;**
;**                                 http://www.zlgmcu.com
;**
;**--------------文件信息--------------------------------------------------------------------------------
;**文   件   名: IRQ.inc
;**创   建   人: 陈明计
;**最后修改日期: 2004年8月27日
;**描        述: 定义IRQ汇编接口代码宏
;**
;**--------------历史版本信息----------------------------------------------------------------------------
;** 创建人: 陈明计
;** 版  本: v1.0
;** 日　期: 2004年8月27日
;** 描　述: 原始版本
;**
;**--------------当前版本修订------------------------------------------------------------------------------
;** 修改人:
;** 日　期:
;** 描　述:
;**
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/

OSNoInt       EQU 0x80
OSSYS32Mode   EQU 0x1f
OSIRQ32Mode   EQU 0x12

;引入的外部标号在这声明
        IMPORT  OSIntCtxSw                      ;任务切换函数
        IMPORT  OSIntExit                       ;中断退出函数
        IMPORT  OSTCBCur
        IMPORT  OSTCBHighRdy
        IMPORT  OSIntNesting                    ;中断嵌套计数器
        IMPORT  OsEnterSum

    MACRO
$IRQ_Label HANDLER $IRQ_Exception_Function
        EXPORT  $IRQ_Label                      ; 输出的标号
$IRQ_Label
        SUB     LR, LR, #4                      ; 计算返回地址
        STMFD   SP!, {R0-R3, R12, LR}           ; 保存任务环境
        MRS     R3, SPSR                        ; 保存状态
        STMFD   SP, {R3, SP, LR}^               ; 保存用户状态的R3,SP,LR,注意不能回写
                                                ; 如果回写的是用户的SP，所以后面要调整SP
        LDR     R2,  =OSIntNesting              ; OSIntNesting++
        LDRB    R1, [R2]
        ADD     R1, R1, #1
        STRB    R1, [R2]
        SUB     SP, SP, #4*3
        MSR     CPSR_c, #(OSNoInt | OSSYS32Mode)    ; 切换到系统模式        
        LDR     R2, =OsEnterSum                 ; OsEnterSum,使OSIntExit退出时中断关闭
        MOV     R1, #1
        STR     R1, [R2]
        ISR     $IRQ_Exception_Function         ; 实际的IRQ处理程序
        MSR     CPSR_c, #(OSNoInt | OSSYS32Mode)    ; 切换到系统模式
        BL      OSIntExit
        LDR     R2, =OsEnterSum                 ; 因为中断服务程序要退出，所以OsEnterSum=0
        MOV     R1, #0
        STR     R1, [R2]

        MSR     CPSR_c, #(OSNoInt | OSIRQ32Mode)    ; 切换回irq模式
        LDMFD   SP, {R3, SP, LR}^               ; 恢复用户状态的R3,SP,LR,注意不能回写
                                                ; 如果回写的是用户的SP，所以后面要调整SP
        LDR     R0, =OSTCBHighRdy
        LDR     R0, [R0]
        LDR     R1, =OSTCBCur
        LDR     R1, [R1]
        CMP     R0, R1
        ADD     SP, SP, #4*3                    ; 
        MSR     SPSR_cxsf, R3
        LDMEQFD SP!, {R0-R3, R12, PC}^          ; 不进行任务切换
        LDR     PC, =OSIntCtxSw                 ; 进行任务切换
    MEND

    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
