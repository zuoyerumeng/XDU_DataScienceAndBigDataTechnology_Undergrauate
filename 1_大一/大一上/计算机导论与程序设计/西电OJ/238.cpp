#include<stdio.h>
 int main()
 {
  int m=4,n=5,a[100][100],i,j,s=0;
  for(i=0;i<m;i++)
  {
  	for(j=0;j<n;j++)
  	  scanf("%d",&a[i][j]);
  }
   for(i=0;i<m;i++)
  {
  	int max=a[i][0];
  	for(j=0;j<n;j++)
  	{
  		if(a[i][j]>max)
  		  max=a[i][j];
	  }
	for(j=0;j<n;j++)
  	{
  		int sum=0;
		if(a[i][j]==max)
  		{
  			for(int k=0;k<m;k++)
  			{
  				if(max>a[k][j])
  				  {
  				  	sum=1;
  				  	break;
					}
			  }
			if(sum==0)
			{
				s=1;
				printf("%d %d %d\n",a[i][j],i+1,j+1);
			}
			break;
		  }
	  }
   }
   if(s==0)
     printf("°°µã²»´æÔÚ");
return 0;
}
