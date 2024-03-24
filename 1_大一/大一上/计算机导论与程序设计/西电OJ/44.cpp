#include<stdio.h>
 int main()
 {
  int n,a[41],i,sum=0;
  scanf("%d",&n);
  a[1]=1;
  a[2]=1;
  for(i=3;i<=40;i++)
  {
  	a[i]=a[i-1]+a[i-2];
  }
  for(i=2;i<a[n];i++)
  {
  	if(a[n]%i==0)
  	sum++;
  }
  if(sum==0)
    printf("yes");
  else
    printf("%d",a[n]);
return 0;
}
