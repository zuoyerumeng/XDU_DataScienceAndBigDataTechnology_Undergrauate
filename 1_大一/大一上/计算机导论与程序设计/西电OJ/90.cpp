#include<stdio.h>
 int main()
{
 int n,a,b,c,sum;
 scanf("%d",&n);
 a=n/100;
 b=(n-a*100)/10;
 c=n-100*a-10*b;
 sum=a+b+c;
 printf("%d",sum);
return 0;
}
