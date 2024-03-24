#include<stdio.h>
 int main()
{
 int a,c,d;
 char b;
 scanf("%d%c%d",&a,&b,&c);
 switch(b)
 {
    case '+':d=a+c;break; 
    case '-':d=a-c;break; 
    case '*':d=a*c;break; 
    case '/':
		if (c != 0)
		{
			d=a/c;
			break; 	
		}
		return 0;
    case '%':
    	if (c != 0)
		{
			d=a%c;
			break; 	
		}
		return 0;
 }
 printf("%d%c%d=%d",a,b,c,d);
return 0;
}
