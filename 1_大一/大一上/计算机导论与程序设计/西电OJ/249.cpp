#include<stdio.h>
 int main()
 {
  int n,sum=0,a[1000];
  scanf("%d",&n);
  for(int i=2;i<=n;i++)
  {
  	while(n%i==0)
  	{
  		n=n/i;
  		a[sum+1]=i;
  		sum++;
	  }
  }
for(int i=1;i<=sum-1;i++)
{
	printf("%d*",a[i]);
}
 printf("%d",a[sum]);
return 0;
}
