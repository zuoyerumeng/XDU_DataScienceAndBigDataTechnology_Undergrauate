#include<stdio.h>
 int main()
 {
  float sum,n;
  scanf("%f",&n);
  if(n>=0&&n<=110)sum=n/2;
  else if(n>110&&n<=210)sum=0.55*(n-10);
  else if(n>210)sum=0.7*n-37;
  printf("%.2f",sum);
return 0;
}
