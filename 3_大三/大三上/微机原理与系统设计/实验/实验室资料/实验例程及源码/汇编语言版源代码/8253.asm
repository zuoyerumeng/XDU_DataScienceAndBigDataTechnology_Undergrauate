COM_ADDR	EQU	0263H
T0_ADDR		EQU	0260H
T1_ADDR		EQU	0261H

_STACK		SEGMENT	STACK	
		DW	100 DUP(?)	
_STACK		ENDS		
			
CODE		SEGMENT		
START		PROC	NEAR	
		ASSUME	CS:CODE, SS:_STACK
		MOV     DX,COM_ADDR
	        MOV     AL,35H
        	OUT     DX,AL			;������T0������ģʽ2״̬,BCD�����
	        MOV     DX,T0_ADDR
	        MOV     AL,00H
	        OUT     DX,AL
	        MOV     AL,10H
	        OUT     DX,AL			;CLK0/1000
	        MOV     DX,COM_ADDR
        	MOV     AL,77H
	        OUT     DX,AL			;������T1Ϊģʽ3״̬���������,BCD�����
        	MOV     DX,T1_ADDR
	        MOV     AL,00H
        	OUT     DX,AL
	        MOV     AL,10H
        	OUT     DX,AL			;CLK1/1000
        	JMP	$			;OUT1���Ƶ��Ϊ1S�ķ���

START		ENDP		
CODE		ENDS		
	        END     START
