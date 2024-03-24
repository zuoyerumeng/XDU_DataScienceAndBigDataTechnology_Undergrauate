#include<stdio.h>
 int main()
 {
  int m,n,a[101][101],b[101][101],i,j;
  scanf("%d%d",&n,&m);
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<=m;j++)
  	{
  	scanf("%d",&a[i][j]);
    }
  }
  for(i=1;i<=m;i++)
  {
  	for(j=1;j<=n;j++)
  	{
  	b[i][j]=a[n+1-j][i];
    }
  }
 for(i=1;i<=m;i++)
  {
  	for(j=1;j<=n;j++)
  	{
         printf("%d ",b[i][j]);
    }
    printf("\n");
  }
return 0;
}
