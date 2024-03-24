#include<stdio.h>
 int main()
{
 int n,sum=1,a[1000],i;	
 scanf("%d",&n);
 for(i=1;i<=n;i++)
 {
 	scanf("%d",&a[i]);
 }
 i=1;
 while(i<=n-1)
 {
 	if(a[i]==a[i+1])
 	   i++;
 	else
 	{
 	   sum++;
 	   i++;
	}
 }
 printf("%d",sum);
return 0;
}
