#include<stdio.h>
 int main()
 {
  int n,a[31],b[31],i;
  float sum=0;
  scanf("%d",&n);
  a[1]=2;
  a[2]=3;
  b[1]=1;
  b[2]=2;
  for(i=3;i<=n;i++)
  {
  	a[i]=a[i-1]+a[i-2];
  	b[i]=b[i-1]+b[i-2];
  }
  for(i=1;i<=n;i++)
  {
  	sum+=(float)a[i]/(float)b[i];
  }
  printf("%.2f",sum);
return 0;
}
