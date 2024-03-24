#include<stdio.h>
 int main()
 {
  int n,k,a[100],i,sum=0;
  scanf("%d%d",&n,&k);
  for(i=0;i<n;i++)
  {
  	scanf("%d",&a[i]);
  	if(a[i]==k)
  	{
  		sum=1;
  		printf("%d ",i);
	  }
  }
  if(sum==0)
    printf("-1");
return 0;
}
