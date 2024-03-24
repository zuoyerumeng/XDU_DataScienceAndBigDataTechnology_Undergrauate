#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int n,a[21],b[21],i,s,S,t;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  	b[i]=a[i];
  }
  	sort(b+1,b+n+1);
  	for(i=1;i<=n;i++)
  	{
  		if(a[i]==b[1])
  		{
  			s=i;
  			break;
		  }
	  }
    	for(i=1;i<=n;i++)
  	{
  		if(a[i]==b[n])
  		{
  			S=i;
  			break;
		  }
	  }
   t=a[s];
   a[s]=a[S];
   a[S]=t;
 for(i=1;i<=n;i++)
     printf("%d ",a[i]);
return 0;
}
