#include<stdio.h>
 int main()
 {
  int n;
  scanf("%d",&n);
  int sum=0;
  for(int i=2;i<n;i++)
  {
  	if(n%i==0)
  	sum++;
  }
  if(sum==0)
  printf("yes");
  else
   printf("no");
return 0;
}
