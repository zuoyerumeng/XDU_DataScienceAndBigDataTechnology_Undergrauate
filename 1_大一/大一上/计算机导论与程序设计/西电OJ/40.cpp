#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int n,a[100],i,d;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  scanf("%d",&a[i]);
  sort(a+1,a+n+1);
  int sum=0;
  d=a[2]-a[1];
  for(i=3;i<=n;i++)
  {
  	if(d!=a[i]-a[i-1])
  	{
  		sum=1;
  		break;
	  }
  }
  if(sum==1)
   printf("no");
  else
   printf("%d",d);
return 0;
}
