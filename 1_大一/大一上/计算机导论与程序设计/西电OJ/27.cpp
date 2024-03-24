#include<stdio.h>
 int main()
{
 float a,sum;	
 scanf("%f",&a);
 if(a>=0&&a<=110)
   sum=0.5*a;
 else if(a>110&&a<=210)
   sum=55+0.55*(a-110);
 else if(a>210)
   sum=110+0.7*(a-210);
 printf("%.2f",sum);
return 0;
}
