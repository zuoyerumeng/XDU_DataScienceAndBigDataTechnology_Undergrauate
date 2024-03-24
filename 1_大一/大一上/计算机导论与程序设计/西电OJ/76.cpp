#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int n,a[30]={0},b[30],i,sum[30]={0},s=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  }
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
  printf("%d:%d\n",b[i],sum[i]);
return 0;
}
