#define COM_ADDR	0x263
#define T0_ADDR		0x260
#define T1_ADDR		0x261
			
#define u8	unsigned char 

extern void outportb( unsigned int, char);

void main()
{
	outportb( COM_ADDR, 0x35);		//������T0������ģʽ2״̬,BCD�����
	outportb( T0_ADDR, 0);
	outportb( T0_ADDR, 0x10);		//CLK0/1000
	outportb( COM_ADDR, 0x77);		//������T1Ϊģʽ3״̬���������,BCD�����
	outportb( T1_ADDR, 0);
	outportb( T1_ADDR, 0x10);		//CLK1/1000
	while (1)						//OUT1���1S�ķ���
	{;}
}

