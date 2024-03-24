
#define	u8	unsigned char
#define u16	unsigned int
#define addr0809	0x250			//0809��ַ

extern void cInitKeyDisplay();
//��pBufferָ���8�ֽڻ�����������ʾ��F5���������
extern void cDisplay8(u8* pBuffer);
extern void outportb( unsigned int, char);
extern char inportb( unsigned int );

void delay(u8* pBuffer)
{
	u16 count = 10;
	while (count--)
	{
		cDisplay8(pBuffer);
	}
}

u8 ad0809()
{
	u8 i = 100;
	outportb(addr0809, 0x0);
	while (i--)
	{;}									//��ʱ,�ȴ�ADת�����
	return inportb(addr0809);
}

void display_data(u16 adResult, u8* pBuffer)
{
	pBuffer[4] = adResult & 0x0f;
	pBuffer[5] = (adResult >> 4);
	pBuffer[2] = adResult / 51 + 0x80;	//255/51 (16���Ƶ�1 = 1/51V) ,0x80:����С����
	adResult = (adResult % 51) * 10;
	pBuffer[1] = adResult / 51;			//��һλС��
	adResult = (adResult % 51) * 10;
	pBuffer[0] = adResult / 51;			//�ڶ�λС��
	pBuffer[3] = 0x10;					//����
	pBuffer[6] = 0x10;
	pBuffer[7] = 0x10;
}

void main()
{
	u8 buffer[8];
	u8 count;
	u16 adResult = 0;
	u16 lastResult = 0xff;
	cInitKeyDisplay();
	while (1)
	{
		if (lastResult != adResult)
		{
			lastResult = adResult;
			display_data(adResult, buffer);
		}
		delay(buffer);
		
		count = 4;					//����4��
		adResult = 0;
		while(count--)
			adResult += ad0809();	//�ۼ�4�εĲ���ֵ
		
		adResult /= 4;				//8�ε�ƽ��ֵ
	}
}

