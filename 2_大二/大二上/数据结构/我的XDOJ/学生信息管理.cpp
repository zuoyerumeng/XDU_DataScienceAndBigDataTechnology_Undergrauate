#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct linklist//�������� 
{
	int sex;
	char name[30];//���� 
	int value;//ѧ��
	struct linklist *next;//ָ����һ�����
}*LinkList;

LinkList InitList(LinkList L)//��ʼ������
{
    L = (LinkList)malloc(sizeof(struct linklist));//ͷ���
	L->next =NULL;
	L->value=0;
	return L;
}

int main()
{
	LinkList L,p,q,r,s;
	int n=0,i=0,j=0,value=0,index=0;
	char name[30],sex;
	L=InitList(L);//ͷָ�� 
	p=L;
	while(1)//������������� 
	{
		r=(LinkList)malloc(sizeof(struct linklist));//����һ���µĽ��
		scanf("%s",name);
		if(strcmp(name,"#") == 0) break;
		scanf("%d %c",&value,&sex);
		if(r->name)
		strcpy(r->name,name);
		r->value = value;
		r->sex=sex;
		p->next = r;
		p = p->next;
		p->next = NULL;
	}
	
	scanf("%d",&n);
	p=L,q=p->next;
	while(q)
	{
		if(q->value!=n)
		{
			q=q->next,p=p->next;
		}
		else
		{
			break;
		}
	}
	if(q)
	{
		if(q->next)//��Ϊ���һ����� 
		{
			p->next=q->next;
		}
		else
		{
			p->next=NULL;
		}
		
		while(L->next)
		{
			printf("%s %d %c\n",L->next->name,L->next->value,L->next->sex);
			L=L->next;
		}	
	}
	
	else
	{
		printf("No\n");
	}
	return 0;
}
