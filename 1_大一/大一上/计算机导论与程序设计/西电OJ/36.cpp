#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int n,a[20][20],i,j,sum,b[41];
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<=n;j++)
  	  scanf("%d",&a[i][j]);
  }
  for(i=1;i<=n;i++)
  {
  	sum=0;
  	for(j=1;j<=n;j++)
  		sum+=a[i][j];
	b[i]=sum;
  }
	for(j=1;j<=n;j++)
  {
  	sum=0;
  	for(i=1;i<=n;i++)
  		sum+=a[i][j];
	b[n+j]=sum;
  }
    sum=0;
    int s=0;
    for(i=1;i<=n;i++) 
    {
    	sum+=a[i][i];
    	s+=a[i][n+1-i];
	}
  b[2*n+1]=sum;
  b[2*n+2]=s;
  sort(b+1,b+2*n+3);
  for(i=2*n+2;i>=1;i--)
    printf("%d ",b[i]);
return 0;
}
