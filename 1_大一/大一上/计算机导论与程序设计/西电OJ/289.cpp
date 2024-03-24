#include<stdio.h>
 int main()
 {
  int n,a[6];
  scanf("%d",&n);
  for(int i=1;i<=5;i++)
  {
  	a[i]=n%10;
  	n=n/10;
  }
   for(int i=5;i>=1;i--)
  printf("%d ",a[i]);
return 0;
}
