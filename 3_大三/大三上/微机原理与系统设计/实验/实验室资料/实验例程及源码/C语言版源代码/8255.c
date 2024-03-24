
#define PA_Addr		0x270
#define PB_Addr		0x271
#define PC_Addr		0x272
#define	CON_Addr	0x273

#define u8	unsigned char 
#define u16	unsigned int 

extern void outportb( unsigned int, char);

void delay(u16 ms)
{
	u16 i;
	while(ms--)
	{
		i = 100;
		do
		{;}while(--i);
	}
}

void main()
{
	u8 i, j;
	u8 led_data[] = {0xbe,						//�����̵ƣ��ϱ����
					 0xbf,						//�����̵���˸���ϱ����
					 0xbd,						//�����Ƶ������ϱ����
					 0xeb,						//������ƣ��ϱ��̵�
					 0xfb,						//������ƣ��ϱ��̵���˸
					 0xdb};						//������ƣ��ϱ��Ƶ���
	outportb(CON_Addr, 0x80);					//PA��PB��PCΪ�������ģʽ
	outportb(PA_Addr, 0xff);					//��ȫϨ��
	while (1)
	{
		outportb(PA_Addr, led_data[0]);			//�����̵ƣ��ϱ����
		delay(5000);
		for (i = 0; i < 6; i++)
		{
			outportb(PA_Addr, led_data[1]);		//�����̵���˸���ϱ����
			delay(500);
			outportb(PA_Addr, led_data[0]);
			delay(500);
		}
		outportb(PA_Addr, led_data[2]);			//�����Ƶ������ϱ����
		delay(3000);
		outportb(PA_Addr, led_data[3]);			//������ƣ��ϱ��̵�
		delay(5000);
		for (i = 0; i < 6; i++)
		{
			outportb(PA_Addr, led_data[4]);		//������ƣ��ϱ��̵���˸
			delay(500);
			outportb(PA_Addr, led_data[3]);
			delay(500);
		}
		outportb(PA_Addr, led_data[5]);			//������ƣ��ϱ��Ƶ���
		delay(3000);
	}
}
