#include<stdio.h>

int main()
{
	int i=0,j=0,k=0,n=0,input[20]={0},error=1;
	int stack[20]={0},s=0;//stackѭ��
	int now[20],left=0;//ʣ��Ԫ�� 
	for(i=0;i<=15;i++)//��ǰʣ��δ��ջԪ�� 
	{
		now[i]=i;
	}
	
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&input[i]);
		if(input[i]>n||input[i]<1)
		{
			error=0;
		}
	}
	
	if(error)
	{
		for(i=1;i<=input[1];i++)
		{
			stack[i]=i,now[i]=0;
		}
		stack[i-1]=0;//��һ��Ԫ�س�ջ 
		s=i-2;//ջ��Ԫ�ظ���
		left=i;//ʣ��ĵ�һ��Ԫ��
		
		for(i=2;i<=n;i++)
		{
			if(input[i]>input[i-1])//����ջ���ٳ�ջ 
			{
				while(stack[s]!=input[i])//һֱ��ջ��ջ��Ԫ���������Ԫ����� 
				{
					stack[s+1]=now[left],now[left]=0;//���ѳ�ջԪ�ص���һ����ʼ��ջ 
					s++,left++;
				}
				stack[s]=0,s--;//���Ԫ����ջ���ջ 
			}
			else//���ջ,����Ԫ�ؿ��ܲ�Ϊջ��Ԫ�� 
			{
				if(stack[s]==input[i])//��ջ�ɹ�
				{
					stack[s]=0,s--;
				}
				else
				{
					error=0;
					break;
				}
			}
		}
	}

	if(error==0)
	{
		printf("no\n");
	}
	else
	{
		printf("yes\n");
	}
	return 0;
}
