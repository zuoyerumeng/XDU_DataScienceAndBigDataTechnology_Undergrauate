#include<stdio.h>
 int main()
 {
  int n,a[100][100],i,j;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<=n;j++)
  	scanf("%d",&a[i][j]);
  }
  for(i=2;i<=n+1;i++)
  {
  	if(i%2==0)
  	{
  		for(j=1;j<=i-1;j++)
  		printf("%d ",a[i-j][j]);
	  }
	else
	{
		for(j=i-1;j>=1;j--)
  		printf("%d ",a[i-j][j]);
	}
  }
   for(i=n+2;i<=2*n;i++)
  {
  	if(i%2==0)
  	{
  		for(j=i-n;j<=n;j++)
  		printf("%d ",a[i-j][j]);
	  }
	else
	{
		for(j=n;j>=i-n;j--)
  		printf("%d ",a[i-j][j]);
	}
  }
return 0;
}
