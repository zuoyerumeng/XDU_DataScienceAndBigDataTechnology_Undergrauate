EXTRN	InitKeyDisplay:NEAR, GetKeyA:NEAR, DisPlay8:NEAR

DAC0832Init	EQU	080H	;DAC0832��ʼ����ֵ

IO8259_0	EQU	0250H
IO8259_1	EQU	0251H
Con_8253	EQU	0263H
T0_8253		EQU	0260H
T1_8253		EQU	0261H
DA0832		EQU	0240H


_STACK		SEGMENT	STACK	
		DW	200 DUP(?)	
_STACK		ENDS		
			
_DATA		SEGMENT	WORD PUBLIC 'DATA'
buffer		DB	8 DUP(0)		;��ʾ��������8���ֽ�
Count		DB	0			;һ��ת������
Count1		DB	0			;ǰһ��
Count2		DB	0			;��ǰһ��
Count3		DB	0			;��ǰһ��
NowCount	DB	0			;��ǰ����ֵ
kpTime		DW	0			;������һ�β���ʱ��ʱ����ֵ
Count500ms	DB	0			;500ms����

bKey		DB	0			;�Ƿ��м�����
bTime		DB	0			;0.25s�����־
bHighKey	DB	0			;����ת��ʮλ

RevSet		DB	0			;����ת��ֵ
RevSetH		DB	0			;��������ת�ٵ�ʮλ��
RevSetL		DB	0			;��������ת�ٵĸ�λ��
Data_0832	DB	0			;DAC0832����ֵ
_DATA		ENDS		
			
CODE		SEGMENT		
START		PROC	NEAR	
		ASSUME	CS:CODE, DS:_DATA, SS:_STACK
		MOV	AX,_DATA	
        	MOV     DS,AX
        	MOV	ES,AX
        	NOP
        	CALL	InitKeyDisplay		;�Լ��̡�����ܿ��Ƶ�Ԫ��ʼ��
		MOV	bKey,0			;�尴����־��1��Ч
		MOV	bHighKey,1		;����ת��ʮλ����־λ
		MOV	Data_0832,DAC0832Init	;��ʼ��ת����ѹ����ֵ
		MOV	RevSet,32H		;��ʼ������ת�٣�50r/s
		MOV	RevSetH,5
		MOV	RevSetL,0
		MOV	bTime,0			;0.25s��־λ,����ȡת�١�����ת�ٱ�־λ
		MOV	Count500ms,1
		MOV	kpTime,0		;������һ�β���ʱ��ʱ����ֵ
		MOV	NowCount,0		;��ǰ����ֵ
		MOV	Count,0			;һ��ת������
		CALL	DAC0832			;��ʼD/A
		CALL	Init8253
		CALL	Init8259
        	CALL	WriIntver
		STI
Main:		CALL	GetKeyA			;��ɨ��
		JNB	Main1
		CALL	Key
		JMP	Main2
Main1:		CMP	bTIME,0			;bTIME:0.25s��ʱ��־
		JZ	MAIN
		MOV	bTIME,0
Main2:		CALL	RateDis			;��ʾת��
		CALL	REVControl		;ת�ٿ���
		JMP	Main

;������
Key		PROC	NEAR
		CMP	AL,10
		JAE	Key2
		CMP	bHighKey,0
		JZ	Key1
		MOV	RevSetH,AL
		MOV	bHighKey,0
		RET
Key1:		MOV	RevSetL,AL
		MOV	AL,RevSetH
		MOV	BL,10
		MUL	BL
		ADD	AL,RevSetL
		MOV	RevSet,AL
		MOV	bHighKey,1
Key2:		RET
Key		ENDP

;ת�ٿ���
REVControl	PROC	NEAR

		MOV	AL,Count		;��ǰת��
		CMP	AL,RevSet		;����ת��
		JZ	REVControl1
		JNB	RevDEC
;���ת��
RevINC:		MOV	Count500ms,1
		MOV	AL,RevSet		;����ת��
		SUB	AL,Count		;��ǰת��
RevINC1:	ADD	AL,Data_0832		;ת�ٲ�ֵ+��һ��DAC0832����ֵ=DAC0832����ֵ
		JNB	RevINC2			;�ж��Ƿ񳬹�DAC0832�������ֵ
		MOV	AL,0FFH	
RevINC2:	MOV	Data_0832,AL
		CALL	DAC0832			;D/A,����DAC0832�����ѹ
		JMP	REVControl1
;����ת��
RevDEC:		MOV	AL,Count		;��ǰת��
		SUB	AL,RevSet		;����ת��
		CMP	AL,40
		JNB	RevDEC1
		MOV	AH,Count500ms
		OR	AH,AH
		JZ	RevDEC3
		MOV	Count500ms,0
RevDEC1:	XCHG	AL,Data_0832		;��һ��DAC0832����ֵ-ת�ٲ�ֵ=DAC0832����ֵ
		SUB	AL,Data_0832
		JNB	RevDEC2
		MOV	AL,10
RevDEC2:	MOV	Data_0832,AL
		CALL	DAC0832			;D/A,����DAC0832�����ѹ		
		JMP	REVControl1
RevDEC3:	INC	Count500ms

REVControl1:	RET
		
REVControl	ENDP

;��ʾת��					
RateDis		PROC	NEAR
		XOR	AH,AH
		MOV	AL,Count
		MOV	BL,10
		DIV	BL
		MOV	buffer,AH
		MOV	buffer+1,AL
		MOV	AL,RevSetL
		MOV	buffer+4,AL
		MOV	AL,RevSetH
		MOV	buffer+5,AL
		
		MOV	buffer+2,10H		;����ʾ
		MOV	buffer+3,10H
		MOV	buffer+6,10H
		MOV	buffer+7,10H
		
		LEA	SI,buffer
		CALL	Display8		;��ʾת�����
		RET
RateDis		ENDP

Timer0Int:	PUSH	AX
		PUSH	DX
		MOV	bTime,1			;0.25s�����־
		MOV	AL,NowCount
		MOV	Count,AL
		MOV	NowCount,0
		SUB	AL,Count1
		JZ	TIMER0_2
		INC	AL
		JZ	TIMER0_2
		CMP	AL,2
		JNZ	TIMER0_3
TIMER0_2:	MOV	AL,Count			;1s����
		PUSH	AX
		XOR	AH,AH
		ADD	AL,Count1
		JNB	TIMER0_4
		INC	AH
TIMER0_4:	ADD	AL,Count2
		JNB	TIMER0_5
		INC	AH
TIMER0_5:	ADD	AL,Count3
		JNB	TIMER0_6
		INC	AH
TIMER0_6:	SHR	AX,2
		MOV	Count,AL
		MOV	AL,Count2
		MOV	Count3,AL
		MOV	AL,Count1
		MOV	Count2,AL
		POP	AX
		MOV	Count1,AL
		JMP	TIMER0_1
TIMER0_3:	MOV	AL,Count
		MOV	Count3,AL			;250ms����
		MOV	Count2,AL
		MOV	Count1,AL
TIMER0_1:	MOV	DX,IO8259_0
		MOV	AL,20H
		OUT	DX,AL
		POP	DX
		POP	AX
		IRET

CountInt:	PUSH	AX
		PUSH	DX
		MOV	DX,Con_8253
        	MOV     AL,40H
	        OUT     DX,AL			;����
	        MOV	DX,T1_8253
	        IN	AL,DX
	        MOV	AH,AL
	        IN	AL,DX
	        XCHG	AL,AH			;T1�ĵ�ǰֵ
	        XCHG	AX,kpTime
	        SUB	AX,kpTime
	        CMP	AX,100
	        JB	CountInt1		;ǰ����β���ʱ���С��100���ж��Ǹ���
		INC	NowCount
CountInt1:	MOV	DX,IO8259_0
		MOV	AL,20H
		OUT	DX,AL
		POP	DX
		POP	AX
		IRET

Init8253	PROC	NEAR
		MOV     DX,Con_8253
	        MOV     AL,34H
        	OUT     DX,AL			;������T0������ģʽ2״̬,HEX����
	        MOV     DX,T0_8253
	        MOV     AL,84H
	        OUT     DX,AL
	        MOV     AL,1EH
	        OUT     DX,AL			;CLK0=31250Hz,250ms��ʱ

	        MOV     DX,Con_8253
        	MOV     AL,74H
	        OUT     DX,AL			;������T1������ģʽ2״̬,HEX����
        	MOV     DX,T1_8253
	        MOV     AL,0FFH
        	OUT     DX,AL
	        MOV     AL,0FFH
        	OUT     DX,AL			;����ʱ��ʹ��
	        
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
		MOV	AL,7EH
		OUT	DX,AL
		RET
Init8259	ENDP

WriIntver	PROC	NEAR
		PUSH	ES
		MOV	AX,0
		MOV	ES,AX
		MOV	DI,20H
		LEA	AX,Timer0Int
		STOSW
		MOV	AX,CS
		STOSW
		MOV	DI,20H + 4 * 7
		LEA	AX,CountInt
		STOSW
		MOV	AX,CS
		STOSW

		POP	ES
		RET
WriIntver	ENDP

;��ģת����A-ת��������
DAC0832		PROC	NEAR
		MOV	DX,DA0832
		MOV	AL,Data_0832
		OUT	DX,AL
		RET
DAC0832		ENDP

START		ENDP		
CODE		ENDS		
		END	START
