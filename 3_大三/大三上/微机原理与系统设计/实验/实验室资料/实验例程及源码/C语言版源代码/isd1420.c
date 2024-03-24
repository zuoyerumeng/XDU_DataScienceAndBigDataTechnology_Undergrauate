#define	u8	unsigned char
#define u16 unsigned int

extern void outportb( unsigned int, char);						//дI/O
extern char inportb( unsigned int );							//��I/O

#define ISD1420_AD1	0x00			//0��4�ż�¼������ʼ��ַ,ÿ��¼������5s
#define ISD1420_AD2	0x28			//1��5�ż�¼������ʼ��ַ
#define ISD1420_AD3	0x50			//2��6�ż�¼������ʼ��ַ
#define ISD1420_AD4	0x78			//3��7�ż�¼������ʼ��ַ

#define I8255_Ctr	0x273			//8255���ƶ˿ڵ�ַ
#define I8255_PA	0x270			//�������������
#define ISDCOMM		0x271	  		//¼������ַ/����ģʽ�����ַ,0F000H��CS1 
#define I8255_PC	0x272			//ISD1420���������


u8 KeepMode;						//����REC��PLAYE��PLAYL��ǰֵ

//���µļ���1��8��ת��Ϊ��Ӧ�ļ�ֵ��0��7�������ڶ��֧������
u8 ScanKey2()
{
	u8 keyResult;
	u8 i = inportb(I8255_PA);
	switch(i)
	{
	case 0xfe:
		keyResult = 0;
		break;
	case 0xfd:
		keyResult = 1;
		break;
	case 0xfb:
		keyResult = 2;
		break;
	case 0xf7:
		keyResult = 3;
		break;
	case 0xef:
		keyResult = 4;
		break;
	case 0xdf:
		keyResult = 5;
		break;
	case 0xbf:
		keyResult = 6;
		break;
	case 0x7f:
		keyResult = 7;
		break;
	default:
		keyResult = 0xff;
	}
	return keyResult;
}

//��ʱ
void Delay20ms()
{
	u16 i = 1320;
	while (--i)
	{;}
}

//����ɨ��
u8 ScanKey()
{
	u8 i;
	u8 KeyResult;
	while (1)
	{
		KeyResult = inportb(I8255_PA);			//��ⰴ������
		if (KeyResult == 0xff)					// ==0xff, �ް�������
			break;
		KeyResult = ScanKey2();
		if (KeyResult == 0xff)
			continue;							//���˲�ֻһ����
		Delay20ms();						//�а�����ȡ����������
		Delay20ms();
		if (KeyResult == ScanKey2())
		{
			do
			{
				i = inportb(I8255_PA);
			}while (i != 0xff);
			break;
		}
	}
	return KeyResult;
}

//��ʱ0.25s�����м��̼�⹦�ܣ�
u8 Delay_025S()
{
	u8 keyResult;
	u16 i = 16000;
	while (i--) {;}
	i = 16000;
	while (i--) {;}
	keyResult = ScanKey();
	return keyResult;
}

//��ʱ
void Delay50ms()
{
	u16 i = 6600;
	while (--i) {;}
}

//��ʼ��
void initISD()
{
	outportb(I8255_PC, 7);					//����ģ���ʼ�����ر�¼��������
	KeepMode = 7;							
	outportb(ISDCOMM, 0);					//�����ֶ�¼����,��A6,A7Ϊ��ʱ���޷��ֶ�����
}

//ֹͣ¼����
void stopISD()
{
	u8 i = (KeepMode & 0xfb);
	outportb(I8255_PC, i);					//PLAYL:һ��������ֹͣ����
	i |= 4;
	outportb(I8255_PC, i);
	i |= 3;					
	outportb(I8255_PC, i);					//1->REC,PLAYE, �ر����в���ָ��
	KeepMode = i;
	outportb(ISDCOMM, 0);					//�����ֶ�¼����,��A6,A7Ϊ��ʱ���޷��ֶ�����
	Delay50ms();
	Delay50ms();
	Delay50ms();
}

//����ģʽ
void modeISD(u8 mode)
{
	u8 i;
	stopISD();								//��ʼ��,REC,PLAYE,PLAYL��λ�����ò���ģʽ
	outportb(ISDCOMM, mode);				//���ò���ģʽ������mode��
	i = KeepMode & 0xfb;
	outportb(I8255_PC, i);					//��PLAYLһ��������,��������
	i |= 4;
	outportb(I8255_PC, i);
	KeepMode = i;
}

//¼��
void recISD(u8 startadr)
{
	u8 i;
	outportb(ISDCOMM, startadr);			//����¼����ʼ��ַ
	i = KeepMode & 0xfe;
	outportb(I8255_PC, i);					//REC��ͣ�����ʼ¼��
	KeepMode = i;
}

//����
void playISD(u8 startadr)
{
	u8 i;
	stopISD();								//��֮ͣǰ��¼��������
	outportb(ISDCOMM, startadr);			//���÷�����ʼ��ַ
	i = KeepMode & 0xfd;
	outportb(I8255_PC, i);					//0->PLAYE ��ʼ����,���ط���ģʽ
	i |= 2;
	outportb(I8255_PC, i);
	KeepMode = i;
}

//�������ʼ��	
void MainInit()
{
	outportb(I8255_Ctr, 0x90);			//8255��ʼ��, PAΪ���룬PC�ĵ���λΪ���
	initISD();
}

//¼���ӳ���	
u8 KEY_REC(u8 startadr)
{
	u8 keyResult;
	u16 count = 20;						//¼��ʱ�䳤��,5s
	recISD(startadr);					//����¼���ӳ���
	while (count--)
	{
		keyResult = Delay_025S();					//��ʱ
		if (keyResult != 0xff)
			return keyResult;			//�м�����
	}
	stopISD();							//ֹͣ¼��
	return 0xff;
}

//����
u8 KEY_PLAY(u8 startadr)
{
	u8 keyResult;
	u16 count = 20;
	playISD(startadr);							//����¼���ӳ���
	while (count--)
	{
		keyResult = Delay_025S();					//��ʱ
		if (keyResult != 0xff)
			return keyResult;			//�м�����
	}
	return 0xff;
}

void main()
{
	u8 keyResult = 0xff;
	MainInit();
	while (1)
	{
		if (keyResult == 0xff)
			keyResult = ScanKey();			//ɨ�谴��
		switch (keyResult)
		{
		case 0:
			keyResult = KEY_REC(ISD1420_AD1);		//0�ż�¼���׵�ַ
			break;
		case 1:
			keyResult = KEY_REC(ISD1420_AD2);		//1�ż�¼���׵�ַ
			break;
		case 2:
			keyResult = KEY_REC(ISD1420_AD3);		//2�ż�¼���׵�ַ
			break;
		case 3:
			keyResult = KEY_REC(ISD1420_AD4);		//3�ż�¼���׵�ַ
			break;
		case 4:
			keyResult = KEY_PLAY(ISD1420_AD1);		//4�ż������׵�ַ
			break;
		case 5:
			keyResult = KEY_PLAY(ISD1420_AD2);		//5�ż������׵�ַ
			break;
		case 6:
			keyResult = KEY_PLAY(ISD1420_AD3);		//6�ż������׵�ַ
			break;
		case 7:
			keyResult = KEY_PLAY(ISD1420_AD4);		//7�ż������׵�ַ
			break;
		default:
			keyResult = 0xff;
		}
	}
}
