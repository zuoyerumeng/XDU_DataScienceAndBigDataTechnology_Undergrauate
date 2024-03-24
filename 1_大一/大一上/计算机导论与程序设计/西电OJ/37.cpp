#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int n,a[101],b[101],c[101],i,sum=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  	if(a[i]%2==0)
  	{
  		b[sum+1]=a[i];
  		sum++;
	  }  	  
  }
  sort(b+1,b+sum+1);
  for(i=sum;i>=1;i--)
    printf("%d ",b[i]);
  sum=0;
  for(i=1;i<=n;i++)
  {
  	if(a[i]%2!=0)
  	{
  		c[sum+1]=a[i];
  		sum++;
	  }  	  
  }
  sort(c+1,c+sum+1);
  for(i=sum;i>=1;i--)
    printf("%d ",c[i]);
return 0;
}
