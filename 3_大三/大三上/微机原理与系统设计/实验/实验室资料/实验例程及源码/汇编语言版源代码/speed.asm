;*******************************************************		
;		ֱ���������ʵ��˵��
;ʵ��Ŀ�ģ�	1.�˽��翪�ز���ԭ��
;		2.����ʹ��MCU����ת�ٲ���
;ʵ�����ݣ�	1.��DAC0832��������磬ʹ�ù�翪�غ�MCU
;		�ļ������������ת��(����4��/ת)���ɶ�ʱ
;		��������ȡ�ź�(250ms/��)ͳ�Ƽ�����������
;		Ϊ������4��/ת��250ms����1�Σ���˶�ȡ��
;		����ֵ��Ϊÿ���ת�٣���ת����ʾ��LED�ϡ�
;		2.ͨ���������ڵ��ת�٣�����ת�ٶ�̬��ʾ
;		LED��;����˵����
;*******************************************************		
EXTRN		InitKeyDisplay:NEAR, DisPlay8:NEAR, GetKeyA:NEAR
IO8259_0	EQU	0250H
IO8259_1	EQU	0251H
Con_8253	EQU	0263H
T0_8253		EQU	0260H
T1_8253		EQU	0261H
DA0832		EQU	0240H

VoltageOffset	EQU	5			;0832��������

_STACK		SEGMENT	STACK	
		DW	100 DUP(?)	
_STACK		ENDS		
			
_DATA		SEGMENT	WORD PUBLIC 'DATA'
buffer		DB	8 DUP(0)		;��ʾ��������8���ֽ�
buffer1		DB	8 DUP(0)		;��ʾ��������8���ֽ�
VOLTAGE		DB	0			;ת����ѹ������
Count		DW	0			;һ��ת������
NowCount	DW	0			;��ǰ����ֵ
kpTime		DW	0			;������һ�β���ʱ��ʱ����ֵ
bNeedDisplay	DB	0			;��Ҫˢ����ʾ
_DATA		ENDS		
			
CODE		SEGMENT		
START		PROC	NEAR	
		ASSUME	CS:CODE, DS:_DATA, SS:_STACK
		MOV	AX,_DATA	
        	MOV     DS,AX
        	MOV	ES,AX
        	NOP
        	CALL	InitKeyDisplay
		MOV	bNeedDisplay,1		;��ʾ��ʼֵ
		MOV	VOLTAGE,99H		;��ʼ��ת����ѹ����ֵ��99H-3.0V
		MOV	Count,0			;һ��ת������
		MOV	NowCount,0		;��ǰ����ֵ
		MOV	kpTime,0		;������һ�β���ʱ��ʱ����ֵ
		CALL	DAC0832			;��ʼD/A
		CALL	Init8253
		CALL	Init8259
		CALL	WriIntver
		STI
MAIN:		CALL	GetKeyA			;����ɨ��
		JNB	Main1
		CMP	AL,00H
		JNZ	Key1
Key0:		MOV	AL,VoltageOffset	;0�ż����£�ת�����
		ADD	AL,VOLTAGE
		CMP	AL,VOLTAGE
		JNB	Key0_1
		MOV	AL,0FFH			;���
Key0_1:		MOV	VOLTAGE,AL
		CALL	DAC0832			;D/A
		JMP	Main2
Key1:		MOV	AL,VOLTAGE		;1�ż����£�ת�ٽ���
		SUB	AL,VoltageOffset
		JNB	Key1_1
		XOR	AL,AL			;��С
Key1_1:		MOV	VOLTAGE,AL
		CALL	DAC0832			;D/A
		JMP	Main2
Main1:		CMP	bNeedDisplay,0
		JZ	MAIN
		MOV	bNeedDisplay,0		;1s��ʱ��ˢ��ת��
Main2:		CALL	RateTest		;����ת��/��ʾ
		JMP	MAIN			;ѭ������ʵ�����ݽ�������ٹ��ܲ���

;ת�ٲ���/��ʾ					
RateTest:	MOV	AX,Count
		MOV	BL,10
		DIV	BL
		CMP	AL,0
		JNZ	RateTest1
		MOV	AL,10H			;��λΪ0������Ҫ��ʾ
RateTest1:	MOV	buffer,AH
		MOV	buffer+1,AL
		MOV	AL,VOLTAGE		;��0832�͵�����
		AND	AL,0FH
		MOV	buffer+4,AL
		MOV	AL,VOLTAGE
		AND	AL,0F0H
		ROR	AL,4
		MOV	buffer+5,AL
		
		MOV	buffer+2,10H		;����ʾ
		MOV	buffer+3,10H
		MOV	buffer+6,10H
		MOV	buffer+7,10H
		
		LEA	SI,buffer
		CALL	Display8		;��ʾת�����
		RET

Timer0Int:	PUSH	AX
		PUSH	DX
		MOV	bNeedDisplay,1
		MOV	AX,NowCount
		SHR	AX,1
		SHR	AX,1
		MOV	Count,AX		;תһȦ,�����ĸ�����,Count = NowCount/4
		MOV	NowCount,0
		MOV	DX,IO8259_0
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
	        MOV     AL,12H
	        OUT     DX,AL
	        MOV     AL,7AH
	        OUT     DX,AL			;CLK0=31250Hz,1s��ʱ

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
		MOV	DI,3CH
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
		MOV	AL,VOLTAGE
		OUT	DX,AL
		RET
DAC0832		ENDP

START		ENDP		
CODE		ENDS		
		END	START
