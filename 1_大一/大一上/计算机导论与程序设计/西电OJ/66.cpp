#include<stdio.h>
 int main()
 {
  int i,n,x[100];
  float p,sum=0;
  scanf("%d",&n);
  for(i=0;i<=n-1;i++)
  {
  	scanf("%d",&x[i]);
  	sum+=x[i];
  }
  p=sum/n;
  printf("%.2f",p);
return 0;
}
