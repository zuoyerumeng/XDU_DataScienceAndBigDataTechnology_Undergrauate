#include<stdio.h>
 int main()
 {
  int m,n,a[257][257],b[16],i,j,k;
  scanf("%d%d",&m,&n);
  for(i=1;i<=m;i++)
  {
  	for(j=1;j<=n;j++)
  	{
  	    scanf("%d",&a[i][j]);
  	    for(k=0;k<=15;k++)
  	    {
  	    	if(a[i][j]==k)
  	    	{
  	    		b[k]+=1;
  	    		break;
			  }
		  }
	}
  }
  for(i=0;i<=15;i++)
  {
  	if(b[i]!=0)
  	   printf("%d %d\n",i,b[i]);
  }
return 0;
}
