#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef struct Person{
	char name[25];
	char sex[5];
	char place[50];
	char phone[15];
	char email[30];
	struct Person *next=NULL;
}Per;

Per *head=NULL;//ͷָ����������ﶼ��Ҫ�õ���������Ϊȫ�ֱ��� 

void Enter()
{
	int input;
	Per *newmember;//������������Ԫ���ǽṹ�� 
	newmember = (Per *)malloc(sizeof(Per));//�����ڴ�
	printf("������������Ϣ��\n");
	printf("���֣�");
    scanf("%s", newmember->name);
    printf("�Ա�");
    scanf("%s", newmember->sex);
    printf("�绰��");
    scanf("%s", newmember->phone);
    printf("���䣺");
    scanf("%s", newmember->email);
    printf("��ͥסַ��");
    scanf("%s", newmember->place);
    newmember->next=head;
    head=newmember;//���ǵ���������������β��������������������һ��β�ڵ㣬���ǽ��˳�Ա��Ϊ��head 
}

void del()
{
	Per *t=head;
	char name[25];//ɾ��������
    printf("������ɾ�����˵����֣�");
    scanf("%s",name);
    if(!head)
	{
		printf("��Ǹ��ͨѶ¼Ϊ�գ�");
		return;
	 } 
    else if(!head->next)//���ֻ��һ����Ϣ
		{
			if(!strcmp(t->name,name))//��ƥ�� 
			{
				head=NULL;
				printf("ɾ���ɹ���"); 
			}
			else printf("��Ǹ���޴���"); 
		 }
	else
	{
		if(!strcmp(t->name,name))//����һ���˾���Ҫɾ���ģ�����Ҫ�޸�head 
		{
			head=t->next;
			printf("ɾ���ɹ���");
			return; 
		}
		while(t->next)//��������Ԫ�� 
		{
			if(!strcmp(t->next->name,name))
			{
				Per *temp;
				temp=t->next;
				t->next=temp->next;
				printf("ɾ���ɹ���"); 
				return;
			}
			t=t->next;
		}
		printf("��Ǹ���޴���"); 
	}
	return;
}

void alloutput()
{
	Per *t=head;
	if(!t) printf("ͨѶ¼Ϊ�գ�");
	 while(t)
    {
        printf("���֣�%s\n",t->name);
        printf("�Ա�%s\n",t->sex);
        printf("�绰��%s\n",t->phone);
        printf("���䣺%s\n",t->email);
        printf("��ͥסַ��%s\n\n",t->place);
        t = t->next;
    }
}

void search()
{
	char target[25];
    printf("������Ҫ��ѯ�˵����֣�");
    scanf("%s",target);
    Per *t=head;
    while(t)
    {
    	if(!strcmp(target,t->name))
    	{
    		printf("��ѯ�ɹ�����Ϣ���£�\n");
            printf("���֣�%s\n",t->name);
            printf("�Ա�%s\n",t->sex);
            printf("�绰��%s\n",t->phone);
            printf("���䣺%s\n",t->email);
            printf("��ͥסַ��%s\n",t->place);
            return;
    	}
    	t = t->next;
    }
    printf("��Ǹ�����޴���\n");
    return; 
}


void save()
{
	Per *t=head;
    FILE *fp;
    char file[15];
    printf("�������ļ�����");
    scanf("%s",file);
    if(!(fp=fopen(file,"w")))
    {
    	printf("��Ǹ���ļ��޷��򿪣�\n");
    	exit(0);
    }
    fprintf(fp,"����\t�Ա�\t�绰\t����\t��ͥסַ?\n");
    while(t)
    {
    	fprintf(fp,"%s\t",t->name);
    	fprintf(fp,"%s\t",t->sex);
    	fprintf(fp,"%s\t",t->phone);
    	fprintf(fp,"%s\t",t->email);
    	fprintf(fp,"%s\t",t->place);
    	t = t -> next;
    }
    printf("Saving file");
    fclose(fp);
}

void load()
{
    FILE* fp = fopen("ͨѶ¼.txt", "r");
    if(!fp)
	{
        printf("��δ�����ļ����޷�����");
        return ;
    }
    if(fgetc(fp) == EOF)
	{
        printf("�ļ�Ϊ�գ��޷����룡\n");
        return;
    }
    rewind(fp);//���ļ��ڲ���λ��ָ������ָ��һ��������/�ļ��Ŀ�ͷ 
    while(1)
	{
        Per* t = (Per *)malloc(sizeof(Per));
        int cnt = fscanf(fp, "%s\n%s\n%s\n%s\n%s\n", t->name, t->sex, t->phone, t->email, t->place);
        if(cnt != 5)
		{
            t = NULL;
            break;
        }
        head->next = t;
        t->next = NULL;
    }
    fclose(fp);
    fp = NULL;
    printf("ͨѶ¼����ɹ�!");
}

int main()
{
	int type;
    printf("������ͨѶ¼����ϵͳ������������ִ�еĲ�����\n");
    printf("1->¼������\n");
    printf("2->��ѯ����\n");
    printf("3->ɾ������\n");
    printf("4->��ʾ����\n");
    printf("5->��������\n");
    printf("6->��������\n");
    printf("7->�˳�\n");
	while(true)
	{
		scanf("%d", &type);
		switch(type)
		{
			case 1 : Enter();
			    break;
			case 2 : search();	
			    break;
			case 3 : del();
			    break;
			case 4 : alloutput();
			    break;
			case 5 : save();
			    break;
			case 6 : load();
			    break;
			case 7 : break;
			default:printf("��Ǹ���޴�ѡ��,������ѡ��");
		}
		if(type==7) break;
		printf("\n���������Ҫִ�еĲ�����"); 
	}
	return 0;
}
