#include<stdio.h>
 int main()
 {
  int n,p=0;
  scanf("%d",&n);
  if(n==0)
    printf("1");
  else
  {
  while(n!=0)
 {
    n=n/10;
    p++;
 }
  printf("%d",p);
  }
return 0;
}
