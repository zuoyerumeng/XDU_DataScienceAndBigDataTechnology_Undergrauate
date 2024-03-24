#include<stdio.h>
 int main()
 {
  int m,n,a[100][100],i,j,s=0;
  scanf("%d%d",&m,&n);
  	for(i=1;i<=m/2;i++)
  	{
  		for(j=i;j<=n+1-i;j++)
  		{
  			s++;
  			a[i][j]=s;
		  }
		for(j=i+1;j<=m+1-i;j++)
		{
			s++;
			a[j][n+1-i]=s;
		}
		for(j=n-i;j>=i;j--)
		{
			s++;
			a[m+1-i][j]=s;
		}
		for(j=m-i;j>=i+1;j--)
		{
			s++;
			a[j][i]=s;
		}
	  }
   if(m%2==1)
   {
   	for(i=(m+1)/2;i<=n+1-(m+1)/2;i++)
   	{
   		s++;
   		a[(m+1)/2][i]=s;
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
