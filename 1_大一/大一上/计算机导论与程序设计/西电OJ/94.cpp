#include<stdio.h>
#include<algorithm>
#include<math.h>
using namespace std;
 int main()
 {
  int i,a[4];
  for(i=0;i<=3;i++)
  {
  	scanf("%d",&a[i]);
  }
  sort(a,a+4);
  for(i=0;i<=3;i++)
  {
  	printf("%d ",a[i]);
  }
return 0;
}
