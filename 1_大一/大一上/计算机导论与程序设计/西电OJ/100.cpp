#include<stdio.h>
 int main()
{
 int a,b,c,l, max;
 scanf("%d%d%d",&a,&b,&c);
 l=a+b+c;
 max = (a>=b && a>=c)?a:(b>=a && b>=c)?b:c;
 if(l>2*max)
   printf("%d",l);
 else
   printf("No");
 return 0;
}
