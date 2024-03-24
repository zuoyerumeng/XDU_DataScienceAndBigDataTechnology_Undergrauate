#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<unordered_map>
#include<malloc.h>
using namespace std;

// 创建两个栈，一个是数据栈，一个是符号栈,由于calculate函数和主函数中都要用到，此处将其设置为全局变量 
int *num,nlen=0,slen=0;//通过底层模拟栈其实也很方便
char *sig;

void calculate()
{
	// 弹出符号栈的一个符号,弹出数据栈的两个操作数，分情况求值后将结果入栈 
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
    // 判断运算符的优先级 
    {
        if(isdigit(str[i]))
        {
            int x=0;
            while(i<strlen(str) && isdigit(str[i])) x=x*10+str[i++]-'0';
            num[nlen++]=x;                        // 数据进数据栈
            if(i==strlen(str)) break;
        }
        if(str[i]=='(') sig[slen++]=str[i];      // 遇到左括号直接入符号栈
        else if(str[i]==')')                      
        {                                        
            while(sig[slen-1]!='(') calculate();     // 遇到右括号，符号栈出栈并运算，直到遇到左括号
            slen--;       
        }
        else
        {
            while(slen && level[sig[slen-1]]>=level[str[i]]) calculate();   // 遇到运算符,判断其与符号栈的优先级, 若小于则运算出结果，直到当前符号优先级大于栈顶 
            sig[slen++]=str[i];       // 然后将当前符号进栈
        }
    }
    while(slen) calculate();
    printf("%d",num[nlen-1]);
    return 0;
}

