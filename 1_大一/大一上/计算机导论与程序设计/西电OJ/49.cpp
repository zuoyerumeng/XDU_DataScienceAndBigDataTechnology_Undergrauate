#include<stdio.h>
#include<math.h>
 int main()
{
 int n;
 double s;	
 scanf("%d",&n);
 s=sqrt((double)n);
 if((s-int(s))==0)
   printf("%.0lf",s);
 else
   printf("no");
return 0;
}
