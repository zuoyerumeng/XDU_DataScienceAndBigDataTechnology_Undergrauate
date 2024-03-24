#include<stdio.h>
 int main()
 {
  int n,a[1000],s=0,i,j,m=0;
  scanf("%d",&n);
  for(i=2;i<n;i++)
  {
  	int sum=0;
  	for(j=2;j<i;j++)
  	{
  		if(i%j==0)
  		sum++;
	  }
	if(sum==0)
    {
    	s++;
    	a[s]=i;
	}	
  }
  for(i=2;i<=s;i++)
  {
  	for(j=i;j<=s;j++)
  	{
  		if(a[j]==n-a[i])
  		{
  			printf("%d %d",a[i],a[j]);
  			m=1;
  			break;
		  }
	  }
	if(m==1)
	  break;
  }
return 0;
}
