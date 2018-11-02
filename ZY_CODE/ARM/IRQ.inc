;/****************************************Copyright (c)**************************************************
;**                               ������������Ƭ����չ���޹�˾
;**                                     ��    ��    ��
;**                                        ��Ʒһ�� 
;**
;**                                 http://www.zlgmcu.com
;**
;**--------------�ļ���Ϣ--------------------------------------------------------------------------------
;**��   ��   ��: IRQ.inc
;**��   ��   ��: ������
;**����޸�����: 2004��8��27��
;**��        ��: ����IRQ���ӿڴ����
;**
;**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
;** ������: ������
;** ��  ��: v1.0
;** �ա���: 2004��8��27��
;** �衡��: ԭʼ�汾
;**
;**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
;** �޸���:
;** �ա���:
;** �衡��:
;**
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/

OSNoInt       EQU 0x80
OSSYS32Mode   EQU 0x1f
OSIRQ32Mode   EQU 0x12

;������ⲿ�����������
        IMPORT  OSIntCtxSw                      ;�����л�����
        IMPORT  OSIntExit                       ;�ж��˳�����
        IMPORT  OSTCBCur
        IMPORT  OSTCBHighRdy
        IMPORT  OSIntNesting                    ;�ж�Ƕ�׼�����
        IMPORT  OsEnterSum

    MACRO
$IRQ_Label HANDLER $IRQ_Exception_Function
        EXPORT  $IRQ_Label                      ; ����ı��
$IRQ_Label
        SUB     LR, LR, #4                      ; ���㷵�ص�ַ
        STMFD   SP!, {R0-R3, R12, LR}           ; �������񻷾�
        MRS     R3, SPSR                        ; ����״̬
        STMFD   SP, {R3, SP, LR}^               ; �����û�״̬��R3,SP,LR,ע�ⲻ�ܻ�д
                                                ; �����д�����û���SP�����Ժ���Ҫ����SP
        LDR     R2,  =OSIntNesting              ; OSIntNesting++
        LDRB    R1, [R2]
        ADD     R1, R1, #1
        STRB    R1, [R2]
        SUB     SP, SP, #4*3
        MSR     CPSR_c, #(OSNoInt | OSSYS32Mode)    ; �л���ϵͳģʽ        
        LDR     R2, =OsEnterSum                 ; OsEnterSum,ʹOSIntExit�˳�ʱ�жϹر�
        MOV     R1, #1
        STR     R1, [R2]
        ISR     $IRQ_Exception_Function         ; ʵ�ʵ�IRQ��������
        MSR     CPSR_c, #(OSNoInt | OSSYS32Mode)    ; �л���ϵͳģʽ
        BL      OSIntExit
        LDR     R2, =OsEnterSum                 ; ��Ϊ�жϷ������Ҫ�˳�������OsEnterSum=0
        MOV     R1, #0
        STR     R1, [R2]

        MSR     CPSR_c, #(OSNoInt | OSIRQ32Mode)    ; �л���irqģʽ
        LDMFD   SP, {R3, SP, LR}^               ; �ָ��û�״̬��R3,SP,LR,ע�ⲻ�ܻ�д
                                                ; �����д�����û���SP�����Ժ���Ҫ����SP
        LDR     R0, =OSTCBHighRdy
        LDR     R0, [R0]
        LDR     R1, =OSTCBCur
        LDR     R1, [R1]
        CMP     R0, R1
        ADD     SP, SP, #4*3                    ; 
        MSR     SPSR_cxsf, R3
        LDMEQFD SP!, {R0-R3, R12, PC}^          ; �����������л�
        LDR     PC, =OSIntCtxSw                 ; ���������л�
    MEND

    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/