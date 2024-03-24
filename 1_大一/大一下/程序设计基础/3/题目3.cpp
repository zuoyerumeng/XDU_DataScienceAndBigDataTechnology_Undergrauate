#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<unordered_map>
#include<malloc.h>
using namespace std;

// ��������ջ��һ��������ջ��һ���Ƿ���ջ,����calculate�������������ж�Ҫ�õ����˴���������Ϊȫ�ֱ��� 
int *num,nlen=0,slen=0;//ͨ���ײ�ģ��ջ��ʵҲ�ܷ���
char *sig;

void calculate()
{
	// ��������ջ��һ������,��������ջ���������������������ֵ�󽫽����ջ 
    int n2=num[-1+nlen];
	nlen--; 
    int n1=num[-1+nlen];
	nlen--; 
    char c=sig[-1+slen--]; 
    switch(c)
    {
    	case '+':num[nlen++]=n1+n2;break;
    	case '-':num[nlen++]=n1-n2;break;
    	case '*':num[nlen++]=n1*n2;break;
    	case '/':num[nlen++]=n1/n2;break;
	}
}

int main() 
{
	num=(int*)malloc(sizeof(int));
	sig=(char*)malloc(sizeof(char));
	unordered_map<char,int> level={{'(',1},{'+', 2}, {'-', 2}, {'*', 3}, {'/', 3}}; 
	char *str;     
    str=(char*)malloc(sizeof(char));
    scanf("%s",str);
    for(int i=0;i<strlen(str);i++)
    // �ж�����������ȼ� 
    {
        if(isdigit(str[i]))
        {
            int x=0;
            while(i<strlen(str) && isdigit(str[i])) x=x*10+str[i++]-'0';
            num[nlen++]=x;                        // ���ݽ�����ջ
            if(i==strlen(str)) break;
        }
        if(str[i]=='(') sig[slen++]=str[i];      // ����������ֱ�������ջ
        else if(str[i]==')')                      
        {                                        
            while(sig[slen-1]!='(') calculate();     // ���������ţ�����ջ��ջ�����㣬ֱ������������
            slen--;       
        }
        else
        {
            while(slen && level[sig[slen-1]]>=level[str[i]]) calculate();   // ���������,�ж��������ջ�����ȼ�, ��С��������������ֱ����ǰ�������ȼ�����ջ�� 
            sig[slen++]=str[i];       // Ȼ�󽫵�ǰ���Ž�ջ
        }
    }
    while(slen) calculate();
    printf("%d",num[nlen-1]);
    return 0;
}

