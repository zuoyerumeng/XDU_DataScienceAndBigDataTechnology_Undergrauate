#include<stdio.h>
 int main()
 {
  int m,n,k[50],t[50],i,j,x;
  float p,sum1,sum2;
  scanf("%d%f%d",&m,&p,&n);
  for(i=1;i<=n;i++)scanf("%d%d",&k[i],&t[i]);
  sum1=0;
  sum2=m*p;
  x=m;
  for(i=1;i<=n;i++)
  {
  		sum1-=k[i]*t[i];
  		x=x+k[i];
  		sum2=(float)x*t[i];
  }
  printf("%.0f",sum1+sum2);
return 0;
}
