#include<stdio.h>
 int main()
 {
  int m,n,a[101]={0},i,j;
  scanf("%d%d",&n,&m);
  for(i=1;i<=m;i++)
  {
  	for(j=1;j<=n;j++)
  	{
  		if(j%i==0)a[j]=1-a[j];
	  }
  }
  for(i=1;i<=n;i++)
  {
  	if(a[i]==1)printf("%d ",i);
  }
return 0;
}
