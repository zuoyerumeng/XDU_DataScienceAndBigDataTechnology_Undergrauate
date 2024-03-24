#include<stdio.h>
 int main()
 {
  int n,a[81],i,max,t;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  }
  max=a[1];
  t=1;
  for(i=2;i<=n;i++)
  {
  	if(a[i]>max)
  	{
  		max=a[i];
  		t=i;
	  }
   }
  printf("%d %d %d",n,max,t-1);
return 0;
}
