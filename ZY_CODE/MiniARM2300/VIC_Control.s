;/****************************************Copyright (c)**************************************************
;**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
;**                                     
;**                               http://www.embedtools.com
;**
;**--------------File Info-------------------------------------------------------------------------------
;** File name: 			VIC_Control.s
;** Last modified Date: 2007-06-12
;** Last Version: 		1.0
;** Descriptions: 		Provide VIC_Control in prerogative mode
;**------------------------------------------------------------------------------------------------------
;** Created by: 		LinEnqiang
;** Created date:   	2007-06-12
;** Version:			1.0
;** Descriptions: 		The original version
;**
;**------------------------------------------------------------------------------------------------------
;** Modified by: 		
;** Modified date:		
;** Version:			
;** Descriptions: 
;********************************************************************************************************/
NoInt       EQU 0x80
NoFIQ		EQU	0x40

SVC32Mode   EQU 0x13
SYS32Mode   EQU 0x1f

VICVectAddr0  EQU 0xfffff100
VICVectAddr   EQU 0xffffff00
VICIntEnClr   EQU 0xfffff014
VICIntSelect  EQU 0xfffff00c
VICProtection EQU 0xFFFFF020 
VICVectPri0   EQU 0xfffff200
VICIntEnable  EQU 0xfffff010
			
			IMPORT  StackUsr 
		
	 		EXPORT  RunFirst
	 		EXPORT  VICControl
	 			 	
	CODE32
    AREA    |RUNFIRST|, CODE, READONLY     
		
RunFirst
;---------------------------------------
;初始化VIC
;Initial VIC And Enable VIC Be Protected;
			
		LDR     R2, =VICIntEnClr
		MVN     R3, #0x00
		STR	    R3, [R2] 
		LDR     R2, =VICIntSelect
		MOV     R3, #0x00
		STR	    R3, [R2] 

        LDR     R0, =VICVectAddr0
        MOV     R1, #0
        MOV     R2, #0
        MOV     R3, #0
        MOV     R4, #0
        MOV     R5, #0
        MOV     R6, #0
        MOV     R7, #0
        MOV     R8, #0
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}
        LDR     R0, =VICVectPri0
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}
        STMIA   R0!, {R1-R8}    		
		
		LDR     R2, =VICVectAddr
		STR	    R3, [R2] 
		LDR     R2, =VICProtection
        MOV     R3, #0x01
        STR	    R3, [R2]              
		MOV     PC, LR 
;----------------------------------------------- 	          
        
VICControl 
        SUB     R0, R0, #0x100
        CMP     R0, #7
        LDRLO   PC, [PC, R0, LSL #2]
        MOVS    PC, LR
SwiFunctionAdd
        DCD     SetVICIRQFunction      ;0
        DCD     FreeVICIRQFunction     ;1
        DCD     ReEnableIRQ            ;2
        DCD     DisableIRQ             ;3
        DCD     GetIRQStatus           ;4
        DCD     EnableVICFIQ           ;5
        DCD     DisableVICFIQ          ;6 
EnableVICFIQ
       	MSR     CPSR_c, #(NoFIQ | NoInt| SVC32Mode)
       	
        CMP     R1, #32							;if (通道号 >=32) return FALSE；
        MOVCS   R0, #0
		MOVCSS  PC, LR
        
        LDR     R0, =VICVectAddr0				;if (IRQ已加载) return FALSE；
        LDR     R3,[R0,R1,LSL #2] 
        CMP     R3,#0
        MOVNE   R0, #0
		MOVNES  PC, LR
        
        LDR     R0, =VICIntSelect				
        LDR     R3, [R0]
        MOV     R2, #1
        MOV     R2, R2, lsl R1 
        ORR     R3, R3, R2                
        STR     R3, [R0]
        
        LDR     R0, =VICIntEnable
        STR     R3, [R0]
        MOV     R0, #1
        MOVS    PC, LR
DisableVICFIQ
		MSR     CPSR_c, #(NoFIQ | NoInt| SVC32Mode)
		
        CMP     R1, #32							;if (通道号 >=32) return FALSE；
        MOVCS   R0, #0
		MOVCSS  PC, LR       
             
        LDR     R0, =VICIntSelect				;if(FIQ未使能)return FALSE
        LDR     R3, [R0]
        MOV     R2, #1
        MOV     R2, R2, LSL R1        
        ANDS    R2, R3, R2        
        MOVEQ   R0, #0
		MOVEQS  PC, LR         
       
        LDR     R0, =VICIntEnClr
        MOV     R3, R2 
        STR     R3, [R0]  						;Disable FIQ
        
        LDR     R0, =VICIntSelect
        LDR     R3, [R0]
        BIC     R3, R3,R2
        STR     R3, [R0]						       
        
        MOV     R0, #1
        MOVS    PC, LR            
ReEnableIRQ
        CMP     R1, #32                         ;if (通道号 >=32) return FALSE;
        MOVCS   R0, #0
        MOVCSS  PC, LR 
        
        LDR     R0, =VICVectAddr0               ;if (未加载) return FALSE；
        LDR     R3, [R0, R1, lsl #2]
        CMP     R3, #0
        MOVEQ   R0, #0
        MOVEQS  PC, LR
		
		LDR     R0, =VICIntEnable
        MOV     R2, #1
        MOV     R3, R2, lsl R1 
        STR     R3, [R0]
        MOV     R0, #1
        MOVS    PC, LR                
DisableIRQ
        CMP     R1, #32                         ;if (通道号 >=32) return FALSE;
        MOVCS   R0, #0
        MOVCSS  PC, LR 
        
        LDR     R0, =VICVectAddr0               ;if (未加载) return FALSE；
        LDR     R3, [R0, R1, lsl #2]
        CMP     R3, #0
        MOVEQ   R0, #0
        MOVEQS  PC, LR
        
        LDR     R0, =VICIntEnClr
        MOV     R2, #1
        MOV     R3, R2, lsl R1 
        STR     R3, [R0]
        MOV     R0, #1
        MOVS    PC, LR
FreeVICIRQFunction
        CMP     R1, #32 						;if (通道号 >=32) return FALSE;
        MOVCS   R0, #0
		MOVCSS  PC, LR
		
		LDR     R0, =VICIntSelect      			;if (FIQ) return FALSE；
        MOV     R3, #1
        MOV     R3, R3, LSL R1 
        LDR     R2, [R0]
        ANDS    R2, R2, R3        
        MOVNE   R0, #0
		MOVNES  PC, LR
        
        LDR     R0, =VICVectAddr0				;if (IRQ was not Set) return FALSE；
        LDR     R2,[R0,R1,LSL #2] 
        CMP     R2,#0
        MOVEQ   R0, #0
		MOVEQS  PC, LR
                
		LDR     R0, =VICIntEnClr       			;Disable IRQ
        STR     R3, [R0]             
        
        LDR     R0, =VICVectAddr0      			;Clear VICVectAddr0
        MOV     R3, #0
        STR     R3, [R0, R1, lsl #2]        
        MOV     R0, #1        
		MOVS    PC, LR
GetIRQStatus
        CMP     R1, #32							;if (通道号 >=32) return FALSE；
        MOVCS   R0, #0
		MOVCSS  PC, LR
        
        LDR     R0, =VICVectAddr0				;if (未加载) return FALSE；
        LDR     R3, [R0, R1, lsl #2]
        CMP     R3, #0
        MOVEQ   R0, #0
		MOVEQS  PC, LR       
        STMIA   R2!, {R1}						;通道号

        LDR     R0, =VICVectPri0
        LDR     R0, [R0, R1, lsl #2]
        STMIA   R2!, {R0}       				;优先级
        STMIA   R2!, {R3}						;处理函数地址

        LDR     R0, =VICIntEnable
        MOV     R3, #1
        MOV     R1, R3, lsl R1 
        LDR     R3, [R0]
        AND     R3, R3, R1            
        CMP     R3, #0
        MOVHI   R3, #1
        STMIA   R2!,{R3}						;IRQ使能与否的状态
        
		MOV     R0, #1
        MOVS    PC, LR 
        
SetVICIRQFunction
        CMP     R1, #32                         ;if (通道号 >=32) return FALSE;
        MOVCS   R0, #0
        MOVCSS  PC, LR
        CMP     R2, #16                         ;if (优先级 >=16) return FALSE;
        MOVCS   R0, #0 
        MOVCSS  PC, LR 
        CMP     R3, #0                          ;if (处理函数 ==0) return FALSE;
        MOVEQ   R0, #0
        MOVEQS  PC, LR
		     
 		MSR     CPSR_c, #(NoFIQ | NoInt | SYS32Mode)
        STMFD   SP!, {R2, R3}
		MOV     R2, #1                          ;if (Enable) return FALSE；
        MOV     R3, R2, lsl R1 
       
        LDR     R0, =VICIntEnable
        LDR     R2, [R0]
        ANDS    R2, R2, R3
        BNE     SetVICIRQFunction_j
        
        LDR     R0, =VICVectAddr0               ;if (IRQ已经使能) return FALSE；
        LDR     R3, [R0, R1, lsl #2]
        CMP     R3, #0         
SetVICIRQFunction_j
        LDMFD   SP!, {R2, R3}
        MSR     CPSR_c, #(NoFIQ | NoInt | SVC32Mode)
        MOVNE   R0, #0
        MOVNES  PC, LR 
        
        STR     R3, [R0, R1, lsl #2]
        LDR     R0, =VICVectPri0
        STR     R2, [R0, R1, lsl #2] 
        
        LDR     R0, =VICIntEnable
        MOV     R2, #1
        MOV     R3, R2, lsl R1 
        STR     R3, [R0]
                                              
        MOV     R0, #1
        MOVS    PC, LR   
         
    END