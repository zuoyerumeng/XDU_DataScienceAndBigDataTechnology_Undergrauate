;8250��PC��ͨ�ţ���Ҫ��PC������һ�������������������8250��ͬ�Ĳ�����
NS8250_Base_Address	EQU	0240H
RHR		EQU   	NS8250_Base_Address    		;�������ݻ�����
THR		EQU	NS8250_Base_Address    		;�������ݻ�����
IER		EQU	NS8250_Base_Address+1		;�жϿ��ƼĴ���
FCR		EQU	NS8250_Base_Address+2		;FIFO���ƼĴ���
ISR		EQU	NS8250_Base_Address+2		;�ж�״̬�Ĵ���
LCR		EQU	NS8250_Base_Address+3		;���пڿ��ƼĴ���
MCR		EQU	NS8250_Base_Address+4		;MODEM���ƼĴ���
LSR		EQU	NS8250_Base_Address+5		;���п�״̬�Ĵ���
MSR		EQU	NS8250_Base_Address+6		;MODEM״̬�Ĵ���	
DLL		EQU	NS8250_Base_Address		;�����ʳ�����������λ
DLM		EQU	NS8250_Base_Address+1		;�����ʳ�����������λ

_STACK		SEGMENT	STACK	
		DW	100 DUP(?)	
_STACK		ENDS		
			
_DATA		SEGMENT	WORD PUBLIC 'DATA'
Receive_Buffer	DB	10 DUP(0)		;���ܻ�����
Send_Buffer	EQU	Receive_Buffer		;���ͻ�����
_DATA		ENDS		
			
CODE		SEGMENT		
START		PROC	NEAR	
		ASSUME	CS:CODE, DS:_DATA, SS:_STACK
		MOV	AX,_DATA	
		MOV	DS,AX
		MOV	ES,AX
		NOP
		CALL	INIT8250
START2:		MOV	CX,10			;��������(�������趨�����ݸ�����
 		CALL	RECEIVE_GROUP
		MOV	CX,10			;�������ݣ������趨�����ݸ�����
		CALL	SEND_GROUP
		JNC	START2
WARNING1:	JMP	$
	
;*************����һ���ַ��ӳ��򣬸�����CX��***********

Send_Group	PROC	NEAR
		LEA	SI,Send_Buffer
Send_Group1:	LODSB
		CALL	Send_Byte
		JC	Send_Group2
		LOOP	Send_Group1
		CLC
Send_Group2:	RET
Send_Group	ENDP		

;*************����һ���ַ��ӳ���,����׵�ַ��DPTR�У�������R6R7��***********
Receive_Group	PROC	NEAR
		LEA	DI,Receive_Buffer
Receive_Group1:	CALL	Receive_Byte
		STOSB
		LOOP	Receive_Group1
		CLC
		RET
Receive_Group	ENDP

INIT8250	PROC	NEAR
		MOV	DX,ISR
        	MOV	AL,06H
        	OUT	DX,AL
        	MOV	DX,LCR
        	MOV	AL,83H		;������ʲ��������ӼĴ���
        	OUT	DX,AL
        	MOV	DX,DLL
        	MOV	AL,40		;������λ�Ĵ�������������Ϊ4800=(3.072*1000000/16)/DLMDLL
		OUT	DX,AL
		MOV	DX,DLM		;00H�͸��ֽڼĴ���
		MOV	AL,00H
		OUT	DX,AL
		MOV	DX,LCR		;��������ʲ��������ӼĴ���	
		MOV	AL,1BH		;���ݸ�ʽΪ8����λ,1ֹͣλ,żУ��
        	OUT	DX,AL
        	RET
INIT8250	ENDP        
	
;*********����һ���ֽ��ӳ��򣬷���A�е�����ʧ����1CY*********        
Send_Byte	PROC	NEAR
		PUSH	CX
		PUSH	AX
      		MOV	CX,1000
      		MOV	DX,LSR
REP11:		IN	AL,DX
      		TEST	AL,20H
      		JNZ	OUTPORT1
      		LOOP	REP11
      		POP	AX
      		STC	
      		JMP	EXIT8250
OUTPORT1:	POP	AX
		MOV	DX,RHR
		OUT	DX,AL
      		CLC
EXIT8250:	POP	CX
      		RET
Send_Byte	ENDP      
;*********����һ���ֽ��ӳ���,�����ֽ���A�У�����ʧ����1CY*********      	     
Receive_Byte	PROC	NEAR
      		MOV	DX,LSR
Receive1:	IN	AL,DX
		TEST	AL,1
		JZ	Receive1
Receive2:	MOV	DX,RHR
		IN	AL,DX
Receive3:	RET
Receive_Byte	ENDP

START		ENDP		
CODE		ENDS		
		END	START
