#include<stdio.h>
 int main()
 {
  int a[1000],sum=0;
  for(int i=1;i<=1000;i++)
  {
  scanf("%d",&a[i]);
  if(a[i]==0)
    break;
  else if(a[i]%2==1)
    sum+=a[i];
  }
  printf("%d",sum);
return 0;
}
