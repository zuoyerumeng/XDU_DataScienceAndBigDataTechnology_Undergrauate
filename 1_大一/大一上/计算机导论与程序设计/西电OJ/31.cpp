#include<stdio.h>
 int main()
{
 int a,b,c;	
 scanf("%d%d",&a,&b);
 if(a!=0&&b!=0)
 {
    c=1;
 while(c!=0)
 {
 	c=a%b;
 	a=b;
 	b=c;
 }
 printf("%d",a);
}
else if((a==0&&b!=0)||(a!=0&&b==0))
   printf("%d",a+b);
return 0;
}
