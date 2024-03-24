extern void outportb( unsigned int, char);						//дI/O
extern char inportb( unsigned int );							//��I/O
extern void enable( void );										//���ж�
extern void disable( void );									//���ж�
extern void setvect( int, void interrupt(*isr)( void ) );		//д�ж�����
extern void interrupt( far *  getvect( int __interruptno ))( );	//���ж�����

#define	u8	unsigned char
#define u16 unsigned int

#define DAC0832Init	0x80		//DAC0832��ʼ����ֵ

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
#define DA0832Addr	0x240

u8 buffer[8];				//��ʾ��������8���ֽ�
u8 count;					//һ��ת������
u8 count1;					//ǰһ��
u8 count2;					//��ǰһ��
u8 count3;					//��ǰһ��
u8 nowCount;				//��ǰ����ֵ
u16 kpTime;					//������һ�β���ʱ��ʱ����ֵ
u8 count500ms;				//500ms����

u8 bKey;					//�Ƿ��м�����
u8 bTime;					//0.25s�����־
u8 bHighKey;				//����ת��ʮλ

u8 RevSet;					//����ת��ֵ
u8 RevSetH;					//��������ת�ٵ�ʮλ��
u8 RevSetL;					//��������ת�ٵĸ�λ��
u8 Data_0832;				//DAC0832����ֵ

//��ģת��
void DAC0832(u8 da_data)
{
	outportb(DA0832Addr, da_data);		//VOLTAGE
}

//ת�ٿ���
void REVControl()
{
	u8 i;
	if (count < RevSet)
	{//���ת��
		count500ms = 1;
		i = RevSet - count + Data_0832;
		if ( i < Data_0832)		//�ж��Ƿ񳬹�DAC0832�������ֵ
			i = 0xff;
		Data_0832 = i;
		DAC0832(i);				//D/A,����DAC0832�����ѹ
	}
	else if (count > RevSet)
	{//����ת��
		i = count - RevSet;
		if (i < 40)
		{
			if (count500ms)
				count500ms = 0;
			else
			{
				count500ms++;
				return;
			}
		}
		i = Data_0832 - i;
		if (i > Data_0832)
			i = 10;
		Data_0832 = i;
		DAC0832(i);				//D/A,����DAC0832�����ѹ
	}
}		

//ת�ٲ���/��ʾ
void RateDis()
{
	u8 i;
	
	if (count > 10)
		buffer[1] = count / 10;
	else
		buffer[1] = 0x10;				//��λΪ0������Ҫ��ʾ
	buffer[0] = count % 10;
	buffer[4] = RevSetL;				//�趨�ٶ�
	buffer[5] = RevSetH;

	buffer[2] = 0x10;
	buffer[3] = 0x10;
	buffer[6] = 0x10;
	buffer[7] = 0x10;
	
	cDisplay8(buffer);					//��ʾת�����
}

void interrupt Timer0Int(void)
{
	u8 i;
	bTime = 1;							//0.25s�����־
	count = nowCount;
	nowCount = 0;
	if ((count == count1) ||
		(count == count1 - 1) ||
		(count == count1 + 1))
	{
		i = (count + count1 + count2 + count3) / 4;
		count3 = count2;
		count2 = count1;
		count1 = count;
		count = i;
	}
	else
	{
		count3 = count2 = count1 = count;
	}	
	outportb(IO8259_0,0x20);
}

void interrupt CountInt(void)
{
	u16 time;
	outportb(Con_8253,0x40);		//����
	time = inportb(T1_8253);
	time += (inportb(T1_8253) << 8);//T1�ĵ�ǰֵ
	if (time - kpTime >= 100)
		nowCount++;					//ǰ����β���ʱ���С��100���ж��Ǹ���
	kpTime = time;
	outportb(IO8259_0,0x20);
}
		
void Init8253()
{
	outportb(Con_8253,0x34);		//������T0������ģʽ2״̬,HEX����
	outportb(T0_8253,0x84);			//CLK0=31250Hz,250ms��ʱ
	outportb(T0_8253,0x1e);

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
			
void main()
{
	u8 i;
	u8 KeyResult;
	cInitKeyDisplay();				//���̡�����ܹ�������ʼ��
	bKey = 0;						//�尴����־��1��Ч
	bHighKey = 1;					//����ת��ʮλ����־λ
	Data_0832 = DAC0832Init;		//��ʼ��ת����ѹ����ֵ
	RevSet = 0x32;					//��ʼ������ת�٣�50r/s
	RevSetH = 5;
	RevSetL = 0;
	bTime = 0;						//0.25s��־λ,����ȡת�١�����ת�ٱ�־λ
	count500ms = 1;
	kpTime = 0;						//������һ�β���ʱ��ʱ����ֵ
	nowCount = 0;					//��ǰ����ֵ
	count = 0;						//һ��ת������
	DAC0832(Data_0832);				//��ʼD/A
	Init8253();
	Init8259();
	WriIntver();
	enable();						//���ж�
	while(1)
	{
		KeyResult = cGetKeyA();
		
		if (KeyResult < 10)
		{
			if (bHighKey)
			{
				bHighKey = 0;
				RevSetH = KeyResult;
			}
			else
			{
				bHighKey = 1;
				RevSetL = KeyResult;
				RevSet = RevSetH * 10 + RevSetL;
			}
		}
		if (bTime)
		{
			bTime = 0;
			RateDis();				//��ʾת��
			REVControl();			//ת�ٿ���
		}
	}	
}	

