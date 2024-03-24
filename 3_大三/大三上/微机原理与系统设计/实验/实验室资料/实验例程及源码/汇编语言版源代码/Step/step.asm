EXTRN	InitKeyDisplay:NEAR, GetKeyA:NEAR, DisPlay8:NEAR

IO8259_0	EQU	0250H
IO8259_1	EQU	0251H
Con_8253	EQU	0263H
T0_8253		EQU	0260H
Con_8255	EQU	0273H
PC_8255		EQU	0272H

_STACK		SEGMENT	STACK	
		DW	100 DUP(?)	
_STACK		ENDS		
			
_DATA		SEGMENT	WORD PUBLIC 'DATA'
StepControl	DB	0		;��һ���͸����������ֵ
buffer		DB	8 DUP(0)	;��ʾ��������8���ֽ�
SpeedNo		DB	0		;ѡ����һ���ٶ�
StepDelay	DB	0		;ת��һ������ʱ����
StartStepDelay	DB	0		;���ѡ����ٶȿ��������ٶȣ���ʱ�ɳ����̣�����ʹ�ö�Ӧ����ʱ����
StartStepDelay1 DB	0		;StartStepDelay
bFirst		DB	0		;��û��ת�����������
bClockwise	DB	0		; =1 ˳ʱ�뷽��  =0 ��ʱ�뷽��ת��
bNeedDisplay	DB	0		;��ת��һ������Ҫ��ʾ�²���
StepCount	DW	0		;��Ҫת���Ĳ���
StepDelayTab:	DB	250,125,83,62,50,42,36,32,28,25,22,21
_DATA		ENDS		
			
CODE		SEGMENT	WORD PUBLIC 'CODE'	
START		PROC	NEAR	
		ASSUME	CS:CODE, DS:_DATA, SS:_STACK
		MOV	AX,_DATA	
        	MOV     DS,AX
        	MOV	ES,AX
        	NOP
        	CALL	InitKeyDisplay
		MOV	bFirst,1		;��û��ת�����������
		MOV	bClockwise,1		;˳ʱ�뷽��
		MOV	StepControl,33H		;��һ���͸����������ֵ
		MOV	SpeedNo,5		;���弶�ٶ�
		CALL	Init8255
		CALL	Init8253
		CALL	Init8259
		CALL	WriIntver
		MOV	buffer,0		;��ʾ��������ʼ��
		MOV	buffer+1,0
		MOV	buffer+2,0
		MOV	buffer+3,0
		MOV	buffer+4,10H
		MOV	AL,SpeedNo
		MOV	buffer+5,AL
		MOV	buffer+6,10H
		MOV	buffer+7,0
STAR2:		LEA	SI,buffer
		CALL	DisPlay8
STAR3:		CALL	GetKeyA
		JB	STAR5
		CMP	bNeedDisplay,0
		JZ	STAR3
		MOV	bNeedDisplay,0
		CALL	Adjust_Step
		JMP	STAR2

STAR5:		CLI				;��ֹ�������ת��
		CMP	AL,10
		JNB	STAR1
		MOV	AH,buffer+2
		MOV	buffer+3,AH
		MOV	AH,buffer+1
		MOV	buffer+2,AH
		MOV	AH,buffer
		MOV	buffer+1,AH
		MOV	buffer,AL
		JMP	STAR2
STAR1:		CMP	AL,14
		JNB	STAR2
		LEA	SI,DriverTab
		SUB	AL,10
		SHL	AL,1
		XOR	AH,AH
		MOV	BX,AX
		JMP	CS:[SI+BX]
DriverTab:	DW	Direction		;ת������
		DW	Speed_up		;���ת��
		DW	Speed_Down		;����ת��
		DW	Exec			;����������ݷ���ת�١�������ʼת��

Direction:	CMP	bClockwise,0
		JZ	Clockwise
		MOV	bClockwise,0
		MOV	buffer+7,1
AntiClockwise:	CMP	bFirst,0
		JZ	AntiClockwise1
		MOV	StepControl,91H
		JMP	Direction1
AntiClockwise1:	MOV	AL,StepControl
		ROR	AL,2
		MOV	StepControl,AL
		JMP	Direction1
Clockwise:	MOV	bClockwise,1
		MOV	buffer+7,0
		CMP	bFirst,0
		JZ	Clockwise1
		MOV	StepControl,33H
		JMP	Direction1
Clockwise1:	MOV	AL,StepControl
		ROL	AL,2
		MOV	StepControl,AL
Direction1:	JMP	STAR2

Speed_up:	MOV	AL,SpeedNo
		CMP	AL,11
		JZ	Speed_up2
Speed_up1:	INC	AL
		MOV	SpeedNo,AL
		MOV	buffer+5,AL
Speed_up2:	JMP	STAR2
Speed_Down:	MOV	AL,SpeedNo
		CMP	AL,0
		JZ	Speed_Down1
		DEC	AL
		MOV	SpeedNo,AL
		MOV	buffer+5,AL
Speed_Down1:	JMP	STAR2

Exec:		MOV	bFirst,0
		CALL	TakeStepCount
		LEA	BX,StepDelayTab
		MOV	AL,SpeedNo
		XLAT
		MOV	StepDelay,AL
		CMP	AL,50
		JNB	Exec1
		MOV	AL,50
Exec1:		MOV	StartStepDelay,AL
		MOV	StartStepDelay1,AL
		STI
		JMP	STAR2

TIMER0:		PUSH	AX
		PUSH	DX
		DEC	StartStepDelay
		JNZ	TIMER0_1
		MOV	AL,StartStepDelay1
		CMP	AL,StepDelay
		JZ	TIMER0_2
		DEC	AL
		MOV	StartStepDelay1,AL
TIMER0_2:	MOV	StartStepDelay,AL
		MOV	AL,StepControl
		MOV	DX,PC_8255
		OUT	DX,AL
		CMP	bClockwise,0
		JNZ	TIMER0_3
		ROR	AL,1
		JMP	TIMER0_4
TIMER0_3:	ROL	AL,1
TIMER0_4:	MOV	StepControl,AL
		CMP	StepCount,0
		JZ	TIMER0_1
		MOV	bNeedDisplay,1
		DEC	StepCount
		JNZ	TIMER0_1
		add	sp,8			;Сд��������ʹ�õ�����������������
		popf
		cli
		pushf
		sub	sp,8
		nop
TIMER0_1:	MOV	DX,IO8259_0
		MOV	AL,20H
		OUT	DX,AL
		POP	DX
		POP	AX
		IRET

Adjust_Step	PROC	NEAR
		MOV	CX,4
		LEA	DI,buffer
		CLD
		MOV	AX,StepCount
		MOV	BX,10
Adjust_Step1:	XOR	DX,DX
		DIV	BX
		XCHG	AX,DX
		STOSB
		MOV	AX,DX
		LOOP	Adjust_Step1
		RET
Adjust_Step	ENDP

TakeStepCount	PROC	NEAR
		MOV	AL,buffer+3		;ת����������StepCount
		MOV	BX,10
		MUL	BL
		ADD	AL,buffer+2
		MUL	BL
		ADD	AL,buffer+1
		ADC	AH,0
		MUL	BX
		ADD	AL,buffer
		ADC	AH,0
		MOV	StepCount,AX
		RET
TakeStepCount	ENDP
		
Init8255	PROC	NEAR
		MOV	DX,Con_8255
		MOV	AL,81H			;PA��PB��PC4-7�����PC0-3����
		OUT	DX,AL
		MOV	DX,PC_8255
		MOV	AL,0FFH
		OUT	DX,AL			;0FFH->8255 PC
		RET
Init8255	ENDP

Init8253	PROC	NEAR
		MOV     DX,Con_8253
	        MOV     AL,35H
        	OUT     DX,AL			;������T0������ģʽ2״̬,BCD�����
	        MOV     DX,T0_8253
	        MOV     AL,10H
	        OUT     DX,AL
	        MOV     AL,02H
	        OUT     DX,AL			;CLK0/210
		RET
Init8253	ENDP

Init8259	PROC	NEAR
		MOV	DX,IO8259_0
		MOV	AL,13H
		OUT	DX,AL
		MOV	DX,IO8259_1
		MOV	AL,08H
		OUT	DX,AL
		MOV	AL,09H
		OUT	DX,AL
		MOV	AL,0FEH
		OUT	DX,AL
		RET
Init8259	ENDP

WriIntver	PROC	NEAR
		PUSH	ES
		MOV	AX,0
		MOV	ES,AX
		MOV	DI,20H
		LEA	AX,TIMER0
		STOSW
		MOV	AX,CS
		STOSW
		POP	ES
		RET
WriIntver	ENDP

START		ENDP		
CODE		ENDS		
		END	START

