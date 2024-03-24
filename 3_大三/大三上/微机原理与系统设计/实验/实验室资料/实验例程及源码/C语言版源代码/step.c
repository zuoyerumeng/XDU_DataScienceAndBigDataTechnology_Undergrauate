/*			������������ۺ�ʵ��
;	       ��0��9�ż������ּ�
;          �ƿ��Ƽ���: A--����ת�л��������Ƶ��������ת
;		       B--���ת�٣�12��ת��
;		       C--����ת��
;		       D--������Ҫת���Ĳ����󣬰���������������Ϊ�㣬һֱת��ȥ���������ͣ�£�
;                                                         ���������Ϊ�㣬ת��ָ��������ͣ�¡�
;	   LED7��ʾ����ת��0������ת��1����ת
;	   LED5��ʾ�ڼ���ת��
;	   LED3..0ת������				*/
extern void outportb( unsigned int, char);						//дI/O
extern char inportb( unsigned int );							//��I/O
extern void enable( void );										//���ж�
extern void disable( void );									//���ж�
extern void setvect( int, void interrupt(*isr)( void ) );		//д�ж�����
extern void interrupt( far *  getvect( int __interruptno ))( );	//���ж�����

#define	u8	unsigned char
#define u16 unsigned int

//�Լ��̡�����ܹ�������ʼ��
extern void cInitKeyDisplay();
//��pBufferָ���8�ֽڻ�����������ʾ��F5���������
extern void cDisplay8(u8* pBuffer);
//����һ��16 ���Ƽ�ֵ�����û�а���������0xff
extern u8 cGetKeyA();

#define	IO8259_0	0x250
#define IO8259_1	0x251
#define Con_8253	0x263
#define T0_8253		0x260
#define IO8255_Con	0x273
#define IO8255_PC	0x272	

u8 StepControl;			//��һ���͸����������ֵ
u8 buffer[8];			//��ʾ��������8���ֽ�
u8 SpeedNo;				//ѡ����һ���ٶ�
u8 StepDelay;			//ת��һ������ʱ����
u8 StartStepDelay;		//���ѡ����ٶȿ��������ٶȣ���ʱ�ɳ����̣�����ʹ�ö�Ӧ����ʱ����
u8 StartStepDelay1;		//StartStepDelay
u16 StepCount;			//ת������

u8 bClockwise;			// =1 ˳ʱ�뷽��  =0 ��ʱ�뷽��ת��
u8 bNeedDisplay;		//��ת��һ������Ҫ��ʾ�²���

//����ת������
void TakeStepCount()
{
	StepCount = ((buffer[3] * 10 + buffer[2])*10 + buffer[1])*10 + buffer[0];
}

//ת������
void Direction()
{
	if (bClockwise )
	{
		bClockwise = 0;
		buffer[7] = 1;
		StepControl = (StepControl >> 2) | (StepControl << 6);
	}
	else
	{
		bClockwise = 1;
		buffer[7] = 0;
		StepControl = (StepControl << 2) | (StepControl >> 6);
	}
}

//�ٶȼӿ�
void Speed_up()
{
	if (SpeedNo != 11)
	{
		SpeedNo++;
		buffer[5] = SpeedNo;
	}
}

//�ٶȼ���
void Speed_Down()
{
	if (SpeedNo)
	{
		SpeedNo--;
		buffer[5] = SpeedNo;
	}
}

void Exec()
{
	u8 StepDelayTab[] = {250,125,83,62,50,42,36,32,28,25,22,21};
	TakeStepCount();
	StepDelay = StepDelayTab[SpeedNo];
	if (StepDelay < 50)
		StartStepDelay = 50;
	else
		StartStepDelay = StepDelay;
		
	StartStepDelay1 = StartStepDelay;
	enable();						//���жϣ������������
}

//ת������-1
void Step_SUB_1()
{
	u8 count = 4;
	u8* pBuffer = buffer;
	while(count--)
	{
		if (*pBuffer != 0)
		{
			*pBuffer -= 1;
			break;
		}
		else
			*pBuffer = 9;
		pBuffer++;
	};
}

void interrupt TIMER0(void)
{
//	--StartStepDelay;
	if (--StartStepDelay)
		goto exit;
	if (StepDelay != StartStepDelay1)
		StartStepDelay1--;
	StartStepDelay = StartStepDelay1;
	outportb(IO8255_PC, StepControl);
//	P1 = ~StepControl;
	if (bClockwise)
		StepControl = (StepControl << 1) | (StepControl >>7);
	else
		StepControl = (StepControl >> 1) | (StepControl <<7);
	
	if (StepCount)
	{
		bNeedDisplay = 1;
		StepCount--;
		Step_SUB_1();
		if (StepCount == 0)
			disable();
	}
exit:
	outportb(IO8259_0,0x20);
	
}

void Init8255()
{
	outportb(IO8255_Con,0x80);		//8255 PC���
	outportb(IO8255_PC, 0xff);		//0FFH->8255 PC
}

void Init8253()
{
	outportb(Con_8253,0x35);		//������T0������ģʽ2״̬,BCD�����
	outportb(T0_8253,0x10);			//CLK0/210
	outportb(T0_8253,0x02);
}

void Init8259()
{
	outportb(IO8259_0,0x13);
	outportb(IO8259_1,0x8);
	outportb(IO8259_1,0x9);
	outportb(IO8259_1,0xfe);
}

void main()
{
	u8 KeyResult;			//��ż�ֵ

	bClockwise = 1;
	StepControl = 0x33;		//��һ���͸����������ֵ
	bNeedDisplay = 0;
	SpeedNo = 5;
	Init8255();
	Init8253();
	Init8259();
	setvect(8, TIMER0);		//��ʼ���ж�����, 8:��8���ж�����,TIMER0:�жϴ������
	
	buffer[0] = 0;
	buffer[1] = 0;
	buffer[2] = 0;
	buffer[3] = 0;
	buffer[4] = 0x10;		//0x10����Ҫ��ʾ
	buffer[5] = SpeedNo;
	buffer[6] = 0x10;
	buffer[7] = 0;
	cInitKeyDisplay();
	while (1)
	{
		cDisplay8(buffer);		//ˢ����ʾ	
		while (1)
		{
			KeyResult = cGetKeyA();
			
			if (KeyResult != 0xff)
			{
				disable();			//�ر��ж�, ��ֹ�������ת��
				if (KeyResult >= 10)
				{
					if (KeyResult >= 14)
						continue;
					switch (KeyResult)
					{
					case 10:		//ת������
						Direction();
						break;
					case 11:		//���ת��
						Speed_up();
						break;
					case 12:		//����ת��
						Speed_Down();
						break;
					case 13:		//����������ݷ���ת�١�������ʼת��
						Exec();
						break;
					}
					break;
				}
				else
				{
					buffer[3] = buffer[2];
					buffer[2] = buffer[1];
					buffer[1] = buffer[0];
					buffer[0] = KeyResult;
					break;
				}
			}
			else
			{
				if (bNeedDisplay)
				{
					bNeedDisplay = 0;
					break;
				}
			}
		}
	}
}

