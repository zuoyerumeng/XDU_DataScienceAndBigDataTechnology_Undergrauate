#include<stdio.h>
#include<math.h>
 int main()
{
 int n,i,cha,sum=0;
 double d[9];	
 scanf("%d",&n);
 cha=n;
 for(i=0;i<=8;i++)
 {
 	d[i]=cha/int(pow(10.0,(double)(8-i)));
	cha=cha%int(pow(10.0,(double)(8-i)));
	sum+=int(d[i]);	
 }
 printf("%d",sum);
return 0;
}
