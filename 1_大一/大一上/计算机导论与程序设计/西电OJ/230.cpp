#include<stdio.h>
 int main()
 {
  int sum=0,a[1000],i,n;
  scanf("%d",&n);
  	for(i=2;i<=n;i++)
  	{
  		int s=0;
  		for(int j=2;j<i;j++)
  		{
  			if(i%j==0)
  			  s++;
		  }
		if(s==0)
		{
		     sum++;
		     a[sum]=i;
	    }
	}
	printf("%d\n",sum);
	for(i=1;i<=sum;i++)
	printf("%d ",a[i]);
return 0;
}
  
  	
