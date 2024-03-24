#include<stdio.h>
 int main()
 {
  int a[6],i;
  for(i=1;i<=5;i++)
  {
  	scanf("%c,",&a[i]);
  }
  for(i=5;i>0;i--)
  printf("%c ",a[i]);
return 0;
}
