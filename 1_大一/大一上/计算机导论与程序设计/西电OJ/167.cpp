#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int n,a[1001]={0},b[1001],i,j,t,sum[1001]={0},s=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  	scanf("%d",&a[i]);
  sort(a+1,a+n+1);
  for(i=1;i<=n;i++)
  {
    if(a[i]>a[i-1])
    {
    	s++;
	   	b[s]=a[i];
	}
		sum[s]++;
  }
  for(i=1;i<=s;i++)
  {
  	for(j=1;j<s;j++)
  	{
  		if(sum[j]<sum[j+1]||(sum[j]==sum[j+1]&&b[j]>b[j+1]))
  		{
  			t=sum[j+1];
  			sum[j+1]=sum[j];
  			sum[j]=t;
  			t=b[j+1];
			b[j+1]=b[j];
			b[j]=t; 		
		 }
	  }
  }
  for(i=1;i<=s;i++)
     printf("%d %d\n",b[i],sum[i]);
return 0;
}
