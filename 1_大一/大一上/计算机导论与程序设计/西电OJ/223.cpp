#include<stdio.h>
 int main()
 {
  int a[4][4],i,j;
  for(i=1;i<=3;i++)
  {
  	for(j=1;j<=3;j++)
  	scanf("%d",&a[i][j]);
  }
  printf("%d",a[1][1]+a[2][2]+a[3][3]);
return 0;
}
