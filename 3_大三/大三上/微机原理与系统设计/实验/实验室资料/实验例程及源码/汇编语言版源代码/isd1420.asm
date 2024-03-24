;*******************************************************		
;		ISD1420 ����ģ������ӳ���	
;ISD1420����ģ�飺20������¼�ţ����ɷ�160�Σ������ƽ
;/�������ַ�ʽ����	
;*******************************************************

;*******************************************************		
;		ISD1420����ģ��ʵ��˵��				
;ʵ��Ŀ�ģ�	1.����¼���������Ļ�������
;		2.���շֶ�¼������������
;ʵ�����ݣ�	��MCU���ƣ�ͨ��F5��8����������¼��������
;		ÿ����������¼������5��
;¼��������	F5��0, 1��2��3�ż��ֱ��¼��5�룻¼��ʱ��
;		B1��DS5�������
;����������	F5��4, 5��6��7�ż��ֱ�ɷ���5�룬����
;		������0, 1��2��3�ż����Ӧ
;*******************************************************
ISD1420_AD0	EQU	00H		;0�ż�¼������ʼ��ַ,ÿ��¼��5s
ISD1420_AD1	EQU	28H		;1�ż�¼������ʼ��ַ
ISD1420_AD2	EQU	50H		;2�ż�¼������ʼ��ַ
ISD1420_AD3	EQU	78H		;3�ż�¼������ʼ��ַ
I8255_Ctr	EQU	0273H		;8255���ƶ˿ڵ�ַ	
I8255_PA	EQU	0270H		;�������������
ISDCOMM		EQU	0271H		;¼������ַ/����ģʽ�����ַ,��8255��PB�ڿ���
I8255_PC	EQU	0272H		;ISD1420���������

_STACK		SEGMENT	STACK	
		DW	100 DUP(?)	
_STACK		ENDS

_DATA		SEGMENT	WORD PUBLIC 'DATA'
KeepMode	DB	7		;����REC��PLAYE��PLAYL��ǰֵ
bNewKey		DB	0		;�м����±�־λ����0-�޼�����
KEYno		DB	0		;��������
KeyTab		DW	KEY0,KEY1,KEY2,KEY3,KEY4,KEY5,KEY6,KEY7	;¼�������������ӳ�����ڵ�ַ
_DATA		ENDS		
			
CODE		SEGMENT
START		PROC	NEAR	
		ASSUME	CS:CODE, DS:_DATA, SS:_STACK
		MOV	AX,_DATA	
		MOV	DS,AX
		NOP		
		CALL	MainInit		;�������ʼ��
Main:		CALL	ScanKey			;ɨ�谴��
		JNB	Main		
Main1:		CALL	KeyRun			;��������
		CMP	bNewKey,0		;�Ƿ����µļ�����
		JZ	Main			
		MOV	bNewKey,0		;�尴����־	
		JMP	Main1			;ѭ������ʵ�����ݽ�����ISD1420���ܲ���
;�������ʼ��		
MainInit	PROC	NEAR
		MOV	bNewKey,0		;�м����±�־λ����0-�޼�����
		MOV	DX,I8255_Ctr		;8255��ʼ��
		MOV	AL,90H			;PAΪ���룬PC�ĵ���λΪ���
		OUT	DX,AL
		CALL	ISD_INIT		;ISD1420��ʼ��
		RET
MainInit	ENDP

;********************************
;¼�����ӳ���					
;********************************
KEY0		PROC	NEAR
		MOV	AL,ISD1420_AD0		;0�ż�¼���׵�ַ
		CALL	KEY_REC		
		RET
KEY0		ENDP				

KEY1		PROC	NEAR
		MOV	AL,ISD1420_AD1		;1�ż�¼���׵�ַ
		CALL	KEY_REC
		RET
KEY1		ENDP
		
KEY2		PROC	NEAR
		MOV	AL,ISD1420_AD2		;2�ż�¼���׵�ַ
		CALL	KEY_REC
		RET
KEY2		ENDP
		
KEY3		PROC	NEAR
		MOV	AL,ISD1420_AD3		;3�ż�¼���׵�ַ
		CALL	KEY_REC
		RET
KEY3		ENDP

;¼���ӳ���		
KEY_REC		PROC	NEAR
		MOV	CX,20			;¼��ʱ�䳤��,5s
		CALL	ISD_REC			;����¼���ӳ���
KEY_REC1:	CALL	Delay_025S		;��ʱ
		CMP	bNewKey,0		;��ⰴ���Ƿ��м�����
		JNZ	KEY_REC2	
		LOOP	KEY_REC1		;¼��ʱ�䣬����CX��ֵ����
		CALL	ISD_STOP		;ֹͣ¼��
KEY_REC2:	RET
KEY_REC		ENDP			

;�����ӳ���
KEY4		PROC	NEAR
		MOV	AL,ISD1420_AD0		;4�ż������׵�ַ
		CALL	KEY_PLAY
		RET
KEY4		ENDP
		
KEY5		PROC	NEAR
		MOV	AL,ISD1420_AD1		;5�ż������׵�ַ
		CALL	KEY_PLAY
		RET
KEY5		ENDP
		
KEY6		PROC	NEAR
		MOV	AL,ISD1420_AD2		;6�ż������׵�ַ
		CALL	KEY_PLAY
		RET
KEY6		ENDP
		
KEY7		PROC	NEAR
		MOV	AL,ISD1420_AD3		;7�ż������׵�ַ
		CALL	KEY_PLAY
		RET
KEY7		ENDP
		
KEY_PLAY	PROC	NEAR
		MOV	CX,20			
		CALL	ISD_PLAY		;����¼���ӳ���
KEY_PLAY1:	CALL	Delay_025S		;���ڽ�����ʾ��ʱ�����
		CMP	bNewKey,0
		JNZ	KEY_PLAY2		;��ⰴ���Ƿ��м�����
		LOOP	KEY_PLAY1		
KEY_PLAY2:	RET
KEY_PLAY	ENDP

KeyRun		PROC	NEAR
		LEA	BX,KeyTab		;�м�����,������Ӧ�������
		MOV	AL,KEYno		;KEYno--����ֵ
		SHL	AL,1			;��2��
	 	XOR	AH,AH			
		ADD	BX,AX			
		CALL	[BX]			;[BX]=��Ӧ�����ӳ�����ڵ�ַ
		RET			
KeyRun		ENDP

;����ɨ��
ScanKey		PROC	NEAR
		MOV	DX,I8255_PA		;8255.PA----��ⰴ������
		IN	AL,DX			;��ɨ��
		CMP	AL,0FFH			
		JNZ	ScanKey1
ScanKey4:	CLC				;�ް�������
		RET
ScanKey1:	CALL	ScanKey2		;�а�����ȡ��������
		JNB	ScanKey4
ScanKey3:	MOV	BL,KEYno
		CALL	Delay20ms		;������
		CALL	Delay20ms
		CALL	ScanKey2
		JNB	ScanKey4
		CMP	BL,KEYno
		JNZ	ScanKey3
ScanKey5:	MOV	DX,I8255_PA
ScanKey6:	IN	AL,DX
		CMP	AL,0FFH
		JNZ	ScanKey6
		STC	
		RET		
ScanKey		ENDP

;���µļ���1��8��ת��Ϊ��Ӧ�ļ�ֵ��0��7�������ڶ��֧������
ScanKey2	PROC	NEAR
		PUSH	BX
		XOR	BL,BL
		MOV	DX,I8255_PA
		IN	AL,DX
		TEST	AL,01H
		JZ	ScanKey21
		INC	BL
		TEST	AL,02H
		JZ	ScanKey21
		INC	BL
		TEST	AL,04H
		JZ	ScanKey21
		INC	BL
		TEST	AL,08H
		JZ	ScanKey21
		INC	BL
		TEST	AL,10H
		JZ	ScanKey21
		INC	BL
		TEST	AL,20H
		JZ	ScanKey21
		INC	BL
		TEST	AL,40H
		JZ	ScanKey21
		INC	BL
		TEST	AL,80H
		JZ	ScanKey21
		CLC	
		JMP	ScanKey22
ScanKey21:	STC			;�м����£����м����±�־
		MOV	KEYno,BL	;��ü�ֵ
ScanKey22:	POP	BX
		RET
ScanKey2	ENDP

;��ʱ
Delay20ms	PROC	NEAR
		PUSH	CX
		MOV	CX,2640
		LOOP	$
		POP	CX
		RET
Delay20ms	ENDP	

;��ʱ0.25s�����м��̼�⹦�ܣ�
Delay_025S	PROC	NEAR
		PUSH	AX
		PUSH	CX
		PUSH	DX
		MOV	CX,28000
		LOOP	$
		MOV	CX,28000
		LOOP	$
		CALL	ScanKey
		JNB	DL1S_2
		MOV	bNewKey,1
DL1S_2:		POP	DX
		POP	CX
		POP	AX
		RET
Delay_025S	ENDP

;¼���ӳ���
;AL--��Ų�����ʽ����ֵ��CX--¼����
ISD_INIT	PROC	NEAR
		MOV	DX,I8255_PC
		MOV	AL,KeepMode
		OR	AL,7			;����ģ���ʼ�����ر�¼��������
		OUT	DX,AL
		MOV	KeepMode,AL
		MOV	DX,ISDCOMM
		XOR	AL,AL
		OUT	DX,AL			;�����ֶ�¼����,��A6,A7Ϊ��ʱ���޷��ֶ�����
		RET
ISD_INIT	ENDP

;����ģʽ��AL-����ģʽ����ֵ
ISD_MODE	PROC	NEAR
		PUSH	AX
		CALL	ISD_STOP		;����ģ���ʼ��,��REC,PLAYE,PLAYL��λ�������ò���ģʽ
		MOV	DX,ISDCOMM		;���ò���ģʽ:�ֶ�¼�� 
		POP	AX
		OUT	DX,AL			;���ò���ģʽ������AL��
		MOV	DX,I8255_PC
		MOV	AL,KeepMode
		AND	AL,0FBH
		OUT	DX,AL
		OR	AL,4
		OUT	DX,AL			;��PLAYLһ��������,��������
		MOV	KeepMode,AL
		RET
ISD_MODE	ENDP

;¼��				
ISD_REC		PROC	NEAR
		MOV	DX,ISDCOMM
		OUT	DX,AL			;����¼����ʼ��ַ
		MOV	DX,I8255_PC
		MOV	AL,KeepMode
		AND	AL,0FEH
		OUT	DX,AL			;REC��ͣ�����ʼ¼��
		MOV	KeepMode,AL
		RET
ISD_REC		ENDP		
;�����ӳ���
;AL--���Ķ���
ISD_PLAY	PROC	NEAR
		PUSH	AX
		CALL	ISD_STOP		;��֮ͣǰ��¼��������
		POP	AX
		MOV	DX,ISDCOMM		;���÷�����ʼ��ַ
		OUT	DX,AL
		MOV	DX,I8255_PC
		MOV	AL,KeepMode
		AND	AL,0FDH
		OUT	DX,AL			;0->PLAYE ��ʼ����,���ط���ģʽ
		OR	AL,2
		OUT	DX,AL			;1->PLAYE
		MOV	KeepMode,AL
		RET
ISD_PLAY	ENDP

;ֹͣ¼����
ISD_STOP	PROC	NEAR
		MOV	DX,I8255_PC
		MOV	AL,KeepMode
		AND	AL,0FBH
		OUT	DX,AL			;PLAYL:һ��������ֹͣ����
		OR	AL,4
		OUT	DX,AL
		CALL	Delay50ms
		OR	AL,3			;1->REC,PLAYE
		OUT	DX,AL			;�ر����в���ָ��
		MOV	KeepMode,AL
		MOV	DX,ISDCOMM
		XOR	AL,AL
		OUT	DX,AL			;�����ֶ�¼����,��A6,A7Ϊ��ʱ���޷��ֶ�����
		RET
ISD_STOP	ENDP	

;��ʱ
Delay50ms	PROC	NEAR
		PUSH	CX
		MOV	CX,13200
		LOOP	$
		POP	CX
		RET
Delay50ms	ENDP

START		ENDP		
CODE		ENDS		
		END	START
