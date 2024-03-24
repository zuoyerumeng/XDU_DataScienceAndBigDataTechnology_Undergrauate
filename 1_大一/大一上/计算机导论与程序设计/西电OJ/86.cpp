#include<stdio.h>
 int main()
 {
  int n,a[101],b[101],c[101],d[101],e[101][101]={0},i,j,k,sum=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  	scanf("%d",&b[i]);
  	scanf("%d",&c[i]);
  	scanf("%d",&d[i]);
  }
  for(i=1;i<=n;i++)
  {
  	for(j=a[i]+1;j<=c[i];j++)
  	{
  		for(k=b[i]+1;k<=d[i];k++)
  		    e[j][k]=1;
	  }
  }
  for(i=1;i<=100;i++)
  {
  	for(j=1;j<=100;j++)
  	{
  		if(e[i][j]==1)
  		    sum++;
	  }
  }
  printf("%d",sum);
return 0;
}
