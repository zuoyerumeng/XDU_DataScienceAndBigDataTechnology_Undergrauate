#include<stdio.h>
 int main()
 {
  int a[4][4],b[4][4],i,j;
  for(i=1;i<=3;i++)
  {
  	for(j=1;j<=3;j++)
  	{
  		scanf("%d",&a[i][j]);
  		b[j][i]=a[i][j];
	  }
  }
  for(i=1;i<=3;i++)
  {
  	for(j=1;j<=3;j++)
  		printf("%d ",b[i][j]+a[i][j]);
  	printf("\n");
   }
return 0;
}
