#include<stdio.h>
 int main()
 {
  int n,a[100],i;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  }
  for(i=n;i>0;i--) printf("%d ",a[i]);
return 0;
}
