#include<stdio.h>
 int main()
 {
  int m,n,a[100][100],i,j,s=0;
  scanf("%d%d",&m,&n);
  for(i=0;i<m;i++)
  {
  	for(j=0;j<n;j++)
  	  scanf("%d",&a[i][j]);
  }
   for(i=0;i<m;i++)
  {
  	int min=a[i][0];
  	for(j=0;j<n;j++)
  	{
  		if(a[i][j]<min)
  		  min=a[i][j];
	  }
	for(j=0;j<n;j++)
  	{
  		int sum=0;
		if(a[i][j]==min)
  		{
  			for(int k=0;k<m;k++)
  			{
  				if(min<a[k][j])
  				  {
  				  	sum=1;
  				  	break;
					}
			  }
			if(sum==0)
			{
				s=1;
				printf("%d %d %d\n",i,j,a[i][j]);
			}
			break;
		  }
	  }
   }
   if(s==0)
     printf("no");
return 0;
}
