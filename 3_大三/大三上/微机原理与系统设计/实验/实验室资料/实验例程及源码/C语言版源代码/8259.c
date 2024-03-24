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

//����һ��ѹ��16���Ƽ�ֵ, pBuffer:��ֵ��Ż�����,������ֵ����һ���ֽ�; length:����(������8��)
//bFlagΪ1:���յ���һ��������,�����ԭ����ʾ������,����ʾ��ֵ
//bFlagΪ0:�������ʾ���ٽ��ռ�����
extern int cGetKey(u8* pBuffer, u16 length, u8 bFlag);

//����һ��16 ���Ƽ�ֵ�����û�а���������0xff
extern u8 cGetKeyA();

//����һ��16 ���Ƽ�ֵ�����û�а�����һֱ�ȴ�
extern u8 cGetKeyB();

//����һ��ѹ��BCD ���ֵ, pBuffer:��ֵ��Ż�����,������ֵ����һ���ֽ�; length:����(������8��)
//bFlagΪ1:���յ���һ��������,�����ԭ����ʾ������,����ʾ��ֵ
//bFlagΪ0:�������ʾ���ٽ��ռ�����
extern int cGetBCDKey(u8* pBuffer, u16 length, u8 bFlag);

#define	IO8259_0	0x250
#define	IO8259_1	0x251

u8	count;						//����жϴ���
u8	ReDisplayFlag;

void Init8259()
{
	outportb(IO8259_0,0x13);
	outportb(IO8259_1,0x8);
	outportb(IO8259_1,0x9);
	outportb(IO8259_1,0xfe);
}

void interrupt INT_0(void)
{
	count++;
	ReDisplayFlag = 1;
	outportb(IO8259_0,0x20);
}

void main()
{
	u8 i;
	u8	Buffer[8];
	disable();					//���ж�
	cInitKeyDisplay();			//��ʼ�����̡�����ܹ�����
	Init8259();
	setvect(8, INT_0);			//��ʼ���ж�����, 8:��8���ж�����,INT_0:�жϴ������
	count = 0;					//�жϴ���
	ReDisplayFlag = 1;			//��Ҫ��ʾ
	Buffer[0] = Buffer[1] = 0;
	for (i = 2; i < 8; i++)			//����λ����Ҫ��ʾ
		Buffer[i] = 0x10;
	enable();					//���ж�
	while(1)
	{
		if (ReDisplayFlag)
		{
			Buffer[0] = count % 10;
			Buffer[1] = count /10;
			ReDisplayFlag = 0;
		}
		cDisplay8(Buffer);
	}
}

