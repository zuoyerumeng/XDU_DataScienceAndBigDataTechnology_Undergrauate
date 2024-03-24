#include<stdio.h>
 int main()
 {
  int p,a[11],b[11],i;
  scanf("%d",&p);
  for(i=1;i<=10;i++)
      a[i]=i;
  for(i=1;i<=9-p;i++)
      b[i]=a[p+1+i];
  for(i=10-p;i<=10;i++)
     b[i]=a[i+p-9];
  for(i=1;i<=10;i++)
      printf("%d ",b[i]);
return 0;
}
