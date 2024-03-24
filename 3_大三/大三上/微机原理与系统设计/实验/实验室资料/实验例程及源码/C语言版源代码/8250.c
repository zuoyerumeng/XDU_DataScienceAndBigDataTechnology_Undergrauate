extern void outportb( unsigned int, char);	//дI/O
extern char inportb( unsigned int );							//��I/O

#define	u8	unsigned char
#define u16 unsigned int

#define	RHR			0x240					//�������ݻ�����
#define THR			0x240					//�������ݻ�����
#define IER			0x241					//�жϿ��ƼĴ���
#define FCR			0x242					//FIFO���ƼĴ���
#define	ISR			0x242					//�ж�״̬�Ĵ���
#define LCR			0x243					//���пڿ��ƼĴ���
#define MCR			0x244					//MODEM���ƼĴ���
#define LSR			0x245					//���п�״̬�Ĵ���
#define MSR			0x246					//MODEM״̬�Ĵ���
#define DLL			0x240					//�����ʳ�����������λ
#define DLM			0x241					//�����ʳ�����������λ

void init8250()
{
	outportb(ISR, 0x6);
	outportb(LCR, 0x83);					//������ʲ��������ӼĴ���
	outportb(DLL, 40);						//��������Ϊ4800=(3.072*1000000/16)/DLMDLL
	outportb(DLM, 0x0);
	outportb(LCR, 0x1b);					//��������ʲ��������ӼĴ���;���ݸ�ʽΪ8����λ,1ֹͣλ,żУ��
}	

//����һ���ֽ�
u8 Receive_Byte()
{
	while ((inportb(LSR) & 1) == 0)		//����״̬
	{;}											//��������
	return inportb(RHR);
}

//����һ������,count--������Ŀ
void Receive_Group(u8* pBuffer, int count)
{
	while(count--)
		*pBuffer++= Receive_Byte();
}

//����һ���ֽ�
int Sendbyte(u8 sdata)
{
	u8 i;
	int j = 1000;
	while ((inportb(LSR) & 0x20) == 0)		//����״̬
	{
		if (j-- == 0)
			return 0;
	}
	outportb(RHR,sdata);
	return 1;
}
	
//����һ������, count--������Ŀ
void Send_Group(u8* pBuffer, int count)
{
	while (count--)
	{
		if (SendByte(*pBuffer++) == 0)
			break;
	}
}

void main()
{
	u8 array[10];
	init8250();						//��ʼ��8250
	while (1)
	{
		Receive_Group(array, 10);	//����10���ֽ�����
		Send_Group(array, 10);		//����10���ֽ�����
	}
}

