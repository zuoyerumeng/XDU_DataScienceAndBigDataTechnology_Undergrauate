WR_COM_AD_L	EQU	0264H			;д�����ָ���ַ
WR_COM_AD_R	EQU	0260H			;д�Ұ���ָ���ַ
WR_DATA_AD_L	EQU	0266H			;д��������ݵ�ַ
WR_DATA_AD_R	EQU	0262H			;д�Ұ������ݵ�ַ
RD_BUSY_AD	EQU	0261H			;��æ��ַ
RD_DATA_AD	EQU	0263H			;�����ݵ�ַ

X		EQU	0B8H			;��ʼ��ʾ�л�ַ
Y		EQU	040H			;��ʼ��ʾ�л�ַ
FirstLine	EQU	0C0H			;��ʼ��ʾ��

_STACK		SEGMENT	STACK	
		DW	100 DUP(?)	
_STACK		ENDS		
			
_DATA		SEGMENT	WORD PUBLIC 'DATA'
;--  ����:  ��  --
Line1_1	DB  000H,000H,0FCH,082H,082H,0AAH,02AH,0AAH,0AAH,0AAH,02AH,002H,002H,0FCH,000H,000H
	DB  000H,0EEH,09BH,090H,098H,094H,095H,080H,080H,080H,095H,095H,095H,095H,0FFH,000H

;--  ����:  ��  --
Line1_2	DB  09EH,062H,002H,002H,002H,032H,0FEH,062H,002H,002H,032H,002H,002H,002H,062H,0DCH
	DB  003H,03CH,040H,040H,046H,040H,0F1H,08EH,080H,040H,07CH,080H,080H,080H,0FEH,003H

;--  ����:  ��  --
Line1_3	DB  000H,0F8H,004H,004H,044H,044H,006H,002H,002H,046H,044H,004H,004H,0F8H,000H,000H
	DB  000H,00FH,010H,010H,011H,011H,0F0H,080H,090H,091H,091H,08CH,084H,087H,0C8H,078H

;--  ����:  ��  --
Line1_4	DB  080H,040H,05EH,052H,052H,052H,032H,072H,082H,082H,042H,062H,052H,04CH,0C0H,000H
	DB  007H,004H,004H,004H,0FCH,08CH,08CH,080H,080H,07CH,004H,004H,004H,004H,007H,000H

;"STAR ES51PRO"
Line2_1	DB  000H,070H,088H,008H,008H,008H,038H,000H,000H,038H,020H,021H,021H,022H,01CH,000H

Line2_2	DB  018H,008H,008H,0F8H,008H,008H,018H,000H,000H,000H,020H,03FH,020H,000H,000H,000H

Line2_3	DB  000H,000H,0C0H,038H,0E0H,000H,000H,000H,020H,03CH,023H,002H,002H,027H,038H,020H

Line2_4	DB  008H,0F8H,088H,088H,088H,088H,070H,000H,020H,03FH,020H,000H,003H,00CH,030H,020H

Line2_5	DB  000H,000H,000H,000H,000H,000H,000H,000H,000H,000H,000H,000H,000H,000H,000H,000H

Line2_6	DB  008H,0F8H,088H,088H,0E8H,008H,010H,000H,020H,03FH,020H,020H,023H,020H,018H,000H

Line2_7	DB  000H,070H,088H,008H,008H,008H,038H,000H,000H,038H,020H,021H,021H,022H,01CH,000H

Line2_8	DB  000H,0F8H,008H,088H,088H,008H,008H,000H,000H,019H,021H,020H,020H,011H,00EH,000H

Line2_9	DB  000H,010H,010H,0F8H,000H,000H,000H,000H,000H,020H,020H,03FH,020H,020H,000H,000H

Line2_10 DB  008H,0F8H,008H,008H,008H,008H,0F0H,000H,020H,03FH,021H,001H,001H,001H,000H,000H

Line2_11 DB  008H,0F8H,088H,088H,088H,088H,070H,000H,020H,03FH,020H,000H,003H,00CH,030H,020H

Line2_12 DB  0E0H,010H,008H,008H,008H,010H,0E0H,000H,00FH,010H,020H,020H,020H,010H,00FH,000H

;--  ����:  ��  --
Line3_1	DB  014H,024H,044H,084H,064H,01CH,020H,018H,00FH,0E8H,008H,008H,028H,018H,008H,000H
	DB  020H,010H,04CH,043H,043H,02CH,020H,010H,00CH,003H,006H,018H,030H,060H,020H,000H

;--  ����:  ӭ  --
Line3_2	DB  040H,041H,0CEH,004H,000H,0FCH,004H,002H,002H,0FCH,004H,004H,004H,0FCH,000H,000H
	DB  040H,020H,01FH,020H,040H,047H,042H,041H,040H,05FH,040H,042H,044H,043H,040H,000H

;--  ����:  ʹ  --
Line3_3	DB  040H,020H,0F0H,01CH,007H,0F2H,094H,094H,094H,0FFH,094H,094H,094H,0F4H,004H,000H
	DB  000H,000H,07FH,000H,040H,041H,022H,014H,00CH,013H,010H,030H,020H,061H,020H,000H

;--  ����:  ��  --
Line3_4	DB  000H,000H,000H,0FEH,022H,022H,022H,022H,0FEH,022H,022H,022H,022H,0FEH,000H,000H
	DB  080H,040H,030H,00FH,002H,002H,002H,002H,0FFH,002H,002H,042H,082H,07FH,000H,000H
		
_DATA		ENDS		
			
CODE		SEGMENT		
START		PROC	NEAR	
		ASSUME	CS:CODE, DS:_DATA, SS:_STACK
		MOV	AX,_DATA	
		MOV	DS,AX
		NOP
START1:		CALL	LCD_INIT		;Һ����ʼ��
		CALL	DelayTime
		CALL	DisLine1		;��2����ʾ"���е���"
		CALL	DelayTime
		CALL	DisLine2		;��3����ʾ"STAR ES51PRO"
		CALL	DelayTime
		CALL	DisLine3		;��4����ʾ"��ӭʹ��"		
		CALL	DelayTime
		JMP	START1
;��ʱ����
DelayTime	PROC	NEAR
		MOV	CX,0
		LOOP	$
		LOOP	$
		RET
DelayTime	ENDP
;��2����ʾ"���е���"
DisLine1	PROC	NEAR
		LEA	SI,Line1_1
		MOV	AL,2			;A-��ʼ��ʾ�е�ַ����2��
		MOV	AH,32			;B-��ʼ��ʾ�е�ַ����32�У�����ͬ
		CALL	WordDISL		;���������ʾһ�����ӳ���
		LEA	SI,Line1_2
		MOV	AL,2
		MOV	AH,48
		CALL	WordDISL
		LEA	SI,Line1_3
		MOV	AL,2
		MOV	AH,0
		CALL	WordDISR		;�Ұ�������ʾһ�����ӳ���
		LEA	SI,Line1_4
		MOV	AL,2
		MOV	AH,16
		CALL	WordDISR
		RET
DisLine1	ENDP		

;��3����ʾ"STAR ES51PRO"
DisLine2	PROC	NEAR
		LEA	SI,Line2_1
		MOV	AL,4			;A-��ʼ��ʾ�е�ַ����4��
		MOV	AH,16			;B-��ʼ��ʾ�е�ַ����16�У�����ͬ
		CALL	ByteDISL		;���������ʾһ���ֽ��ӳ���
		LEA	SI,Line2_2
		MOV	AL,4
		MOV	AH,24		
		CALL	ByteDISL
		LEA	SI,Line2_3
		MOV	AL,4
		MOV	AH,32
		CALL	ByteDISL
		LEA	SI,Line2_4		
		MOV	AL,4
		MOV	AH,40
		CALL	ByteDISL
		LEA	SI,Line2_5
		MOV	AL,4
		MOV	AH,48
		CALL	ByteDISL
		LEA	SI,Line2_6		
		MOV	AL,4
		MOV	AH,56
		CALL	ByteDISL		
		LEA	SI,Line2_7
		MOV	AL,4
		MOV	AH,0
		CALL	ByteDISR		;�Ұ����ֽ���ʾ����
		LEA	SI,Line2_8
		MOV	AL,4
		MOV	AH,8
		CALL	ByteDISR
		LEA	SI,Line2_9
		MOV	AL,4
		MOV	AH,16		
		CALL	ByteDISR
		LEA	SI,Line2_10
		MOV	AL,4
		MOV	AH,24
		CALL	ByteDISR
		LEA	SI,Line2_11
		MOV	AL,4
		MOV	AH,32
		CALL	ByteDISR		
		LEA	SI,Line2_12
		MOV	AL,4
		MOV	AH,40
		CALL	ByteDISR
		RET
DisLine2	ENDP		

;��4����ʾ"��ӭʹ��"
DisLine3	PROC	NEAR
		LEA	SI,Line3_1		
		MOV	AL,6			;A-��ʼ��ʾ�е�ַ����6��
		MOV	AH,32			;B-��ʼ��ʾ�е�ַ����32�У�����ͬ
		CALL	WordDISL		;���������ʾһ�����ӳ���
		LEA	SI,Line3_2
		MOV	AL,6
		MOV	AH,48
		CALL	WordDISL
		LEA	SI,Line3_3
		MOV	AL,6
		MOV	AH,0
		CALL	WordDISR		;�Ұ�������ʾһ�����ӳ���
		LEA	SI,Line3_4
		MOV	AL,6
		MOV	AH,16
		CALL	WordDISR
		RET
DisLine3	ENDP		

;Һ����ʼ��	
LCD_INIT	PROC	NEAR
		MOV	AL,3EH	 		;��ʼ�������������ʾ
		CALL	WRComL			;дָ���ӳ���
		MOV	AL,FirstLine		;������ʼ��ʾ�У���0��
		CALL	WRComL
		MOV	AL,3EH	 		;��ʼ���Ұ���������ʾ
		CALL	WRComR			;дָ���ӳ���
		MOV	AL,FirstLine		;������ʼ��ʾ�У���0��
		CALL	WRComR
		CALL	LCDClear		;����
		MOV	AL,3FH			;����ʾ
		CALL	WRComL
		MOV	AL,3FH			;����ʾ
		CALL	WRComR
		RET
LCD_INIT	ENDP
;����
LCDClear	PROC	NEAR
;�������
		MOV	AL,0			;��ʼ�У���0��
		MOV	AH,0			;��ʼ�У���0��
LCDClearL1:	PUSH	AX
		MOV	CX,64
		CALL	SETXYL			;������ʼ��ʾ���е�ַ
LCDClearL2:	MOV	AL,0
		CALL	WRDATAL
		LOOP	LCDClearL2
		POP	AX
		INC	AX
		CMP	AL,8			;��8��
		JNZ	LCDClearL1	
		;���Ұ���
		MOV	AL,0			;��ʼ�У���0��
		MOV	AH,0			;��ʼ�У���0��
LCDClearR1:	PUSH	AX
		MOV	CX,64
		CALL	SETXYR			;������ʼ��ʾ���е�ַ
LCDClearR2:	XOR	AL,AL
		CALL	WRDATAR
		LOOP	LCDClearR2		
		POP	AX
		INC	AL
		CMP	AL,8			;��8��
		JNZ	LCDClearR1
		RET
LCDClear	ENDP

;***************************************
;��ʾ���壬��ʾһ������Ҫռ��X������λ��
;***************************************
;�������ʾһ���ֽ�/�֣�AL-��ʼ��ʾ������X(0-7)��AH-��ʼ��ʾ������Y(0-63)��SI-��ʾ�������׵�ַ
ByteDisL	PROC	NEAR
		MOV	CX,8			;��ʾ8���ֽ����ݣ�������ʾһ��Ӣ��/����
		CALL	DispL
		RET
ByteDisL	ENDP
		
WordDisL	PROC	NEAR
		MOV	CX,16			;��ʾ16�ֽ����ݣ�������ʾһ������
		CALL	DispL
		RET
WordDisL	ENDP

DispL		PROC	NEAR
		PUSH	AX
		PUSH	CX
		CALL	SETXYL			;������ʼ��ʾ���е�ַ
		CALL	DisplayL		;��ʾ�ϰ�������
		POP	CX
		POP	AX
		INC	AL
		CALL	SETXYL			;������ʼ��ʾ���е�ַ
		CALL	DisplayL		;��ʾ�°�������
		RET	
DispL		ENDP

;�Ұ�����ʾһ���ֽ�/�֣�AL-��ʼ��ʾ������X(0-7)��AH-��ʼ��ʾ������Y(0-63)��SI-��ʾ�������׵�ַ
ByteDisR	PROC	ENAR
		MOV	CX,8			;��ʾ8���ֽ����ݣ�������ʾһ��Ӣ��/����
		CALL	DispR
		RET
ByteDisR	ENDP
		
WordDisR	PROC	NEAR
		MOV	CX,16			;��ʾ16�ֽ����ݣ�������ʾһ������
		CALL	DispR
		RET
WordDisR	ENDP
		
DispR		PROC	NEAR
		PUSH	AX
		PUSH	CX
		CALL	SETXYR			;������ʼ��ʾ���е�ַ
		CALL	DisplayR		;��ʾ�ϰ�������
		POP	CX
		POP	AX
		INC	AL
		CALL	SETXYR			;������ʼ��ʾ���е�ַ
		CALL	DisplayR		;��ʾ�°�������
		RET	
DispR		ENDP

;***************************************
;��ʾͼ��		
;***************************************
;��ʾ�����һ��ͼ��,AL-X��ʼ������(0-7)��AH-Y��ʼ�е�ַ����(0-63)
LineDisL	PROC	NEAR
		MOV	CX,64		
		CALL	SETXYL			;������ʼ��ʾ����
		CALL	DisplayL		;��ʾ����
		RET
LineDisL	ENDP		
;��ʾ�Ұ���һ��ͼ��,AL-X��ʼ�е�ַ����(0-7)��AH-Y��ʼ�е�ַ����(0-63)
LineDisR	PROC	NEAR
		MOV	CX,64
		CALL	SETXYR			;������ʼ��ʾ����
		CALL	DisplayR		;��ʾ����
		RET		
LineDisR	ENDP

;***************************************
;��������		
;***************************************
;��ʾ��������ݣ�R7-��ʾ���ݸ���
DisplayL	PROC	NEAR
		LODSB
		CALL	WRDataL			;д���������
		LOOP	DisplayL
		RET
DisplayL	ENDP

;��ʾ�Ұ������ݣ�R7-��ʾ���ݸ���
DisplayR	PROC	NEAR
		LODSB
		CALL	WRDataR			;д���������
		LOOP	DisplayR
		RET
DisplayR	ENDP

;�����������ʼ��ʾ���е�ַ,AL-X��ʼ������(0-7)��AH-Y��ʼ������(0-63)
SETXYL		PROC	NEAR
		OR	AL,X			;�е�ַ=������+�л�ַ
		CALL	WRComL
		MOV	AL,AH
		OR	AL,Y			;�е�ַ=������+�л�ַ
		CALL	WRComL
		RET
SETXYL		ENDP

;�����Ұ�����ʼ��ʾ���е�ַ,AL-X��ʼ������(0-7)��AH-Y��ʼ������(0-63)
SETXYR		PROC	NEAR
		OR	AL,X			;�е�ַ=������+�л�ַ
		CALL	WRComR
		MOV	AL,AH
		OR	AL,Y			;�е�ַ=������+�л�ַ
		CALL	WRComR
		RET
SETXYR		ENDP

;д���������ָ�A-д��ָ��
WRComL		PROC	NEAR
		MOV	DX,WR_COM_AD_L	
		OUT	DX,AL
WRComL1:	MOV	DX,RD_BUSY_AD
		IN	AL,DX
		TEST	AL,80H			;���Һ����ʾ�Ƿ���æ״̬
		JNZ	WRComL1
		RET
WRComL		ENDP


;д�Ұ�������ָ�A-д��ָ��
WRComR		PROC	NEAR
		MOV	DX,WR_COM_AD_R
		OUT	DX,AL
WRComR1:	MOV	DX,RD_BUSY_AD
		IN	AL,DX
		TEST	AL,80H			;���Һ����ʾ�Ƿ���æ״̬
		JNZ	WRComR1
		RET	
WRComR		ENDP

;д��������ݣ�A-д������	
WRDataL		PROC	NEAR
		MOV	DX,WR_DATA_AD_L
		OUT	DX,AL
WRDataL1:	MOV	DX,RD_BUSY_AD
		IN	AL,DX
		TEST	AL,80H			;���Һ����ʾ�Ƿ���æ״̬
		JNZ	WRDataL1
		RET	
WRDataL		ENDP


;д�Ұ������ݣ�A-д������	
WRDataR		PROC	NEAR
		MOV	DX,WR_DATA_AD_R
		OUT	DX,AL
WRDataR1:	MOV	DX,RD_BUSY_AD
		IN	AL,DX
		TEST	AL,80H			;���Һ����ʾ�Ƿ���æ״̬
		JNZ	WRDataR1
		RET
WRDataR		ENDP
		
START		ENDP		
CODE		ENDS		
		END	START
