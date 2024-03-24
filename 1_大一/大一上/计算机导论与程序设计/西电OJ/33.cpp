#include<stdio.h>
double function(int n);
 int main()
 {
  int n;
  scanf("%d",&n);
  printf("%.6lf",function(n));
return 0;
}
 double function(int n)
{
  double a[11];
  int i;
  a[1]=(double)1;
  for(i=2;i<=n;i++)
  {
  	a[i]=(double)1/(double)(1+a[i-1]);
  }
  return(a[n]);
}
