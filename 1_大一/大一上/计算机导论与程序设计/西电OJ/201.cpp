#include<stdio.h>
 int main()
 {
  int a[11],b[10],i;
  for(i=1;i<=10;i++)
  	scanf("%d",&a[i]);
  for(i=1;i<10;i++)
  {
  	b[i]=a[i+1]/a[i];
    printf("%d ",b[i]);
  }
return 0;
}
