#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int m,n,a[8][8],b[50],i,j,sum=0;
  scanf("%d%d",&m,&n);
  for(i=1;i<=m*n;i++)
      scanf("%d",&b[i]);
  sort(b+1,b+m*n+1);
  for(i=1;i<=m;i++)
  {
  	if(i%2==1)
  	{
  		for(j=n;j>0;j--)
  		{
  			sum++;
			a[i][j]=b[sum];
		  }
	  }
	else 
	{
		for(j=1;j<=n;j++)
	     {
	     	sum++;
	     	a[i][j]=b[sum];
		 }
	} 
  }
  
  for(i=1;i<=m;i++)
  {
  	for(j=1;j<=n;j++)
  	   printf("%d ",a[i][j]);
  	printf("\n");
  }
return 0;
}
