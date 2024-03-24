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

Per *head=NULL;//头指针各个函数里都需要用到，所以设为全局变量 

void Enter()
{
	int input;
	Per *newmember;//运用链表，链表元素是结构体 
	newmember = (Per *)malloc(sizeof(Per));//申请内存
	printf("请输入以下信息：\n");
	printf("名字：");
    scanf("%s", newmember->name);
    printf("性别：");
    scanf("%s", newmember->sex);
    printf("电话：");
    scanf("%s", newmember->phone);
    printf("邮箱：");
    scanf("%s", newmember->email);
    printf("家庭住址：");
    scanf("%s", newmember->place);
    newmember->next=head;
    head=newmember;//考虑到若将其置于链表尾部还需遍历链表或再设置一个尾节点，于是将此成员作为新head 
}

void del()
{
	Per *t=head;
	char name[25];//删除的名字
    printf("请输入删除的人的名字：");
    scanf("%s",name);
    if(!head)
	{
		printf("抱歉，通讯录为空！");
		return;
	 } 
    else if(!head->next)//如果只有一条信息
		{
			if(!strcmp(t->name,name))//若匹配 
			{
				head=NULL;
				printf("删除成功！"); 
			}
			else printf("抱歉，无此人"); 
		 }
	else
	{
		if(!strcmp(t->name,name))//若第一个人就是要删除的，那需要修改head 
		{
			head=t->next;
			printf("删除成功！");
			return; 
		}
		while(t->next)//遍历链表元素 
		{
			if(!strcmp(t->next->name,name))
			{
				Per *temp;
				temp=t->next;
				t->next=temp->next;
				printf("删除成功！"); 
				return;
			}
			t=t->next;
		}
		printf("抱歉，无此人"); 
	}
	return;
}

void alloutput()
{
	Per *t=head;
	if(!t) printf("通讯录为空！");
	 while(t)
    {
        printf("名字：%s\n",t->name);
        printf("性别：%s\n",t->sex);
        printf("电话：%s\n",t->phone);
        printf("邮箱：%s\n",t->email);
        printf("家庭住址：%s\n\n",t->place);
        t = t->next;
    }
}

void search()
{
	char target[25];
    printf("请输入要查询人的名字：");
    scanf("%s",target);
    Per *t=head;
    while(t)
    {
    	if(!strcmp(target,t->name))
    	{
    		printf("查询成功，信息如下：\n");
            printf("名字：%s\n",t->name);
            printf("性别：%s\n",t->sex);
            printf("电话：%s\n",t->phone);
            printf("邮箱：%s\n",t->email);
            printf("家庭住址：%s\n",t->place);
            return;
    	}
    	t = t->next;
    }
    printf("抱歉，查无此人\n");
    return; 
}


void save()
{
	Per *t=head;
    FILE *fp;
    char file[15];
    printf("请输入文件名：");
    scanf("%s",file);
    if(!(fp=fopen(file,"w")))
    {
    	printf("抱歉，文件无法打开！\n");
    	exit(0);
    }
    fprintf(fp,"名字\t性别\t电话\t邮箱\t家庭住址?\n");
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
    FILE* fp = fopen("通讯录.txt", "r");
    if(!fp)
	{
        printf("还未创建文件！无法载入");
        return ;
    }
    if(fgetc(fp) == EOF)
	{
        printf("文件为空，无法载入！\n");
        return;
    }
    rewind(fp);//将文件内部的位置指针重新指向一个数据流/文件的开头 
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
    printf("通讯录输入成功!");
}

int main()
{
	int type;
    printf("这里是通讯录管理系统，请输入你想执行的操作：\n");
    printf("1->录入数据\n");
    printf("2->查询数据\n");
    printf("3->删除数据\n");
    printf("4->显示数据\n");
    printf("5->保存数据\n");
    printf("6->加载数据\n");
    printf("7->退出\n");
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
			default:printf("抱歉，无此选项,请重新选择！");
		}
		if(type==7) break;
		printf("\n请继续输入要执行的操作："); 
	}
	return 0;
}
