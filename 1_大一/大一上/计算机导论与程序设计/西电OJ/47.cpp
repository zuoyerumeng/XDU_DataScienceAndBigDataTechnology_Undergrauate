#include<stdio.h>
 int main()
{
 int a;
 float b,t,T;	
 scanf("%d%f",&a,&b);
 t=a+b/60;
 T=4*t*t/(t+2)-20;
 printf("%.2f",T);
return 0;
}
