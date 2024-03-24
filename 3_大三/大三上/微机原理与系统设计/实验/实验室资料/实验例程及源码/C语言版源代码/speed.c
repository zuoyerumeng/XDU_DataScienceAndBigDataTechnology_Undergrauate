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
#define T1_8253		0x261
#define DA0832		0x240

#define VoltageOffset	5	//0832��������

u8 buffer[8];				//��ʾ��������8���ֽ�
u8 VOLTAGE;					//ת����ѹ������
u8 Count;					//һ��ת������
u16 NowCount;				//��ǰ����ֵ
u16 kpTime;					//������һ�β���ʱ��ʱ����ֵ
u8 bNeedDisplay;			//��Ҫˢ����ʾ


//ת�ٲ���/��ʾ
void RateTest()
{
	u8 i;
	u8 buffer1[8];
	
	if (Count > 10)
		buffer[1] = Count / 10;
	else
		buffer[1] = 0x10;				//��λΪ0������Ҫ��ʾ
	buffer[0] = Count % 10;

	buffer[5] = (VOLTAGE >> 4);			//��0832�͵�����
	buffer[4] = (VOLTAGE & 0xf);
	
	buffer[2] = 0x10;
	buffer[3] = 0x10;
	buffer[6] = 0x10;
	buffer[7] = 0x10;
	
	for (i = 0; i < 8; i++)
		buffer1[i] = buffer[i];
	cDisplay8(buffer);					//��ʾת�����
}

void interrupt Timer0Int(void)
{
	bNeedDisplay = 1;
	Count = NowCount / 4;			//תһȦ����4������,Count=NowCount/4
	NowCount = 0	;
	outportb(IO8259_0,0x20);
}

void interrupt CountInt(void)
{
	u16 time;
	outportb(Con_8253,0x40);		//����
	time = inportb(T1_8253);
	time += (inportb(T1_8253) << 8);//T1�ĵ�ǰֵ
	if (time - kpTime >= 100)
		NowCount++;					//ǰ����β���ʱ���С��100���ж��Ǹ���
	kpTime = time;
	outportb(IO8259_0,0x20);
}
		
void Init8253()
{
	outportb(Con_8253,0x34);		//������T0������ģʽ2״̬,HEX����
	outportb(T0_8253,0x12);			//CLK0=31250Hz,1s��ʱ
	outportb(T0_8253,0x7a);

	outportb(Con_8253,0x74);		//������T1������ģʽ2״̬,HEX����
	outportb(T1_8253,0xff);			//����ʱ��ʹ��
	outportb(T1_8253,0xff);

}

void Init8259()
{
	outportb(IO8259_0,0x13);
	outportb(IO8259_1,0x8);
	outportb(IO8259_1,0x9);
	outportb(IO8259_1,0x7e);
}

//�ж�����	
void WriIntver()
{
	setvect(8, Timer0Int);
	setvect(0xf, CountInt);
}

//��ģת��
void DAC0832(u8 da_data)
{
	outportb(DA0832, da_data);		//VOLTAGE
}

			
void main()
{
	u8 i;
	u8 KeyResult;
	bNeedDisplay = 1;				//��ʾ��ʼֵ
	VOLTAGE = 0x99;					//��ʼ��ת����ѹ����ֵ��99H-3.0V
	Count = 0;						//һ��ת������
	NowCount = 0;					//��ǰ����ֵ
	kpTime = 0;						//������һ�β���ʱ��ʱ����ֵ
	DAC0832(VOLTAGE);				//��ʼD/A
	Init8253();
	Init8259();
	WriIntver();
	cInitKeyDisplay();				//���̡�����ܹ�������ʼ��
	enable();						//���ж�
	
	while (1)
	{
		KeyResult = cGetKeyA();
		
		if (KeyResult != 0xff)
		{
			if(KeyResult == 0)
			{//0�ż����£�ת�����
				i = VOLTAGE + VoltageOffset;
				if ( i < VOLTAGE)
					i = 0xff;
				VOLTAGE = i;
				DAC0832(VOLTAGE);
			}
			else if (KeyResult == 1)
			{//1�ż����£�ת�ٽ���
				i = VOLTAGE - VoltageOffset;
				if (i > VOLTAGE)
					i = 0;
				VOLTAGE = i;
				DAC0832(VOLTAGE);
			}
		}
		else
		{
			if (bNeedDisplay)
			{
				bNeedDisplay = 0;			//1s��ʱ��ˢ��ת��
				RateTest();				//����ת��/��ʾ
			}
		}
	}
}	
