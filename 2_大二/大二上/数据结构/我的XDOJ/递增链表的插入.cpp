#include<stdio.h>
#include<stdlib.h>
typedef struct linklist//�������� 
{
	int value;//��ֵ 
	struct linklist *next;//ָ����һ��Stack
}*LinkList;
LinkList InitList(LinkList L)//��ʼ������
{
    L = (LinkList)malloc(sizeof(LinkList));//ͷ���
	L->value = 0;
	L->next =NULL;
	return L;
}
int main()
{
	LinkList L,p,q,r,s;
	int n=0,i=0,j=0,value=0;
	scanf("%d %d",&n,&value);

	L=InitList(L);//ͷָ��
	s=InitList(s);
	p=L,s->value=value;
	for(i=0;i<n;i++)//������������� 
	{
		r=(LinkList)malloc(sizeof(LinkList));//����һ���µĽ��
		scanf("%d",&value);
		r->value = value;
		p->next = r;
		p = p->next;
		p->next = NULL;
	}
	
	p=L,q=p->next;
	while(q)
	{
		if(q->value > s->value)//���в���
		{
			p->next=s,s->next=q;
			break;
		}
		p=p->next,q=q->next;
	}
	
	if(q==NULL)//��β������ 
	{
		p->next=s;
	}
	
	while(L->next->next)
	{
		printf("%d ",L->next->value);
		L=L->next;
	}
	printf("%d",L->next->value);
	printf("\n");	
	return 0;
}
