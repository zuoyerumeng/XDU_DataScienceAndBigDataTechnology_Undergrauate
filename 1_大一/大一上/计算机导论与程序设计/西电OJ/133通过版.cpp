#include <stdio.h>
#include <string.h>

struct ooo	//�ýṹ�������ⷽ�����
{
    int coe;
    int exp;
};

int main()
{
    int n,m,t;
    scanf("%d%d%d",&n,&m,&t);
    struct ooo a[200],b[100],temp;
    int i=0,j=0,k=0,l=0;
    for(i=0;i<n;++i)	//��ϲ����++i,��˵��ĳЩ����¿��Լӿ������ٶȣ�������ʲô�����Ҳ��֪�����ֶ�����*2��
    {
        scanf("%d%d",&a[i].coe,&a[i].exp);
    }
    for(i=0;i<m;++i)
    {
        scanf("%d%d",&b[i].coe,&b[i].exp);
    }
    int tt=1;	//���tt����������Ҳ��֪�����ֶ�����*3��
    if(t)
        tt=-1;
    for(i=0;i<n;++i)	//����a�����b�������ָ����ȵ��Ȼ�󡣡���
    {
        for(j=0;j<m;++j)	
        {
            if(b[j].coe&&a[i].exp==b[j].exp)	//���ָ�����
            {
                a[i].coe+=tt*b[j].coe;	//ʹa�����ϵ���ӻ��b�����ϵ��������tt�Ժ󷽱����
                b[j].coe=0;	//��b���������ָ����Ӧ��ϵ����0�����Ѿ�û�����ü�ֵ�ˣ������ᰭ�£�����
            }
        }
    }
    j=0; 
    for(i=0;i<m;++i)	//����b����
    {
        if(b[i].coe)	//b������ĳһ���ϵ����Ϊ0��˵����һ���ָ��������a�����е�����һ���ָ��
        {
            a[n+j].coe=tt*b[i].coe;	//ǧ����������tt
            a[n+j].exp=b[i].exp;
            ++j;
        }
    }
    l=j;
 /*   for(i=0;i<n+l;++i)	//����ע��������bug���µĲ�������Ĵ���Ҳ����bugҲ��������������
    {
        printf("coe:%d exp:%d\n",a[i].coe,a[i].exp);
    }*/
    for(i=0;i<n+l-1;++i)	//ѡ�����򷨣����������ﻹ�и����ʵ�����
    {
        k=i;
        for(j=i+1;j<n+l;++j)
        {
            if(a[k].exp>a[j].exp)k=j;	//��ָ����С��������
        }
        temp=a[i];
        a[i]=a[k];
        a[k]=temp;
    }
/*    for(i=0;i<n+l;++i)
    {
        printf("coe:%d exp:%d\n",a[i].coe,a[i].exp);
    }*/
//    printf("N:%d L:%d\n",n,l);
	int x1=1,x2=0;	//x1�ж��Ƿ�������ϵ����Ϊ0��1�����ǣ�0�����x2�ж��Ƿ�Ϊ��һ�������0��1��
    for(i=0;i<n+l;++i)	//forѭ���ڲ����Լ򻯣�����̫����
    {					//����������ܿ����Ļ����򻯲�������
        if(a[i].coe)	//�����һ��ϵ��Ϊ0�������������
        {
//        	printf("...\n");
            if(x2&&a[i].coe>0)printf("+");	//������ǵ�һ������򼴽��������һ��ϵ��С��0���Ͳ�Ҫ����Ӻ�
            x1=0;x2=1;	//���Ѿ�����ˣ�˵��������������ϵ����Ϊ0��������һ���Ժ���������ǵ�һ�����
            if(a[i].coe==1)	//ϵ������1�ͱ���ʡ��ϵ��
            {
                if(a[i].exp==1)	//ָ������1�ͱ���ʡ��^���ź�ָ��
                {
                    printf("x");
                }
                else if(a[i].exp==0)	//ָ��Ϊ0ֱ�����ϵ��������x��������Ҫ���
                {
                    printf("%d",a[i].coe);
                }
                else	//�����x^ָ����
                {
                    printf("x^%d",a[i].exp);
                }
            }
            else if(a[i].coe==-1)	//ϵ������-1Ҳ����ʡ��ϵ�����ڡ�x��ǰ����ϡ�-��
            {
                if(a[i].exp==1)	//ͬ��
                {
                    printf("-x");
                }
                else if(a[i].exp==0)	//ͬ��
                {
                    printf("%d",a[i].coe);
                }
                else	//������
                {
                    printf("-x^%d",a[i].exp);
                }
            }
            else
            {
                if(a[i].exp==1)
                {
                    printf("%dx",a[i].coe);
                }
                else if(a[i].exp==0)
                {
                    printf("%d",a[i].coe);
                }
                else
                {
                    printf("%dx^%d",a[i].coe,a[i].exp);
                }
            }
        }
    }
    if(x1)	//���x1����1��˵���������Ϊ0������δ���������ô��Ҫ���0
    {
        printf("0");
    }
    return 0;
}


