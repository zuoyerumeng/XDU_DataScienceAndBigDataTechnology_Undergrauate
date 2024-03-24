#include<stdio.h>
 int main()
{
 int t;
 float sum,s;
 scanf("%f%d",&s,&t);
 if(s<=3)
    sum=10;
 else if(s>3&&s<=10)
    sum=10+2*(s-3);
 else
    sum=24+3*(s-10);
 sum+=t/5*2; 
 printf("%.0f",sum);
return 0;
}
