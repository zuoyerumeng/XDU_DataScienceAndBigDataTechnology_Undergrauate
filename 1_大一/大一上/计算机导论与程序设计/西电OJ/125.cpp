#include<stdio.h>
#include<math.h>
 int main()
{
 float r,n;
 double p;	
 scanf("%f%f",&r,&n);
 p=pow((double)(1+r),(double)n);
 printf("%.2lf",p);
return 0;
}
