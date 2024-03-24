#include<stdio.h>
 int main()
 {
  int m,n,a[100][100],b[100],c[100],i,j,sum,s;
  scanf("%d%d",&m,&n);
  for(i=0;i<m;i++)
  {
  	for(j=0;j<n;j++)
  	scanf("%d",&a[i][j]);
  }
  for(i=0;i<m;i++)
  {
  	int S=0;
	sum=0;
  	for(j=0;j<n;j++)
  	sum+=a[i][j];
  	if(sum==0)
  	  printf("-1 -1\n");
  	else
  	{
  		for(j=0;j<n;j++)
  		{
  			if(a[i][j]==1)
  			{				
				S++;
				s=1;
  				for(int k=j+1;k<n;k++)
  				{
  					if(a[i][k]==1)
  					  s++;
  					else
  					  break;
				  }
				b[S]=s;
				c[S]=j;
				j+=s;
			  }
		  }
		}
		int max=b[1];
		for(j=1;j<=S;j++)
		{
			if(b[j]>max)
			  max=b[j];
		}
		for(j=1;j<=S;j++)
		{
			if(b[j]==max)
			printf("%d %d\n",c[j],c[j]+max-1);
	  }
  }
return 0;
}
