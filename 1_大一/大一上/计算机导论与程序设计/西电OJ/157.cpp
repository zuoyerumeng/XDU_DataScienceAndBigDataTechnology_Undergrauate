#include<stdio.h>
 int main()
 {
  int n,sum=0;
  scanf("%d",&n);
  int i=1;
  while(i<=n)
  {
  	sum+=i;
  	i++;
  }
  printf("%d",sum);
return 0;
}
