#include<stdio.h>
#include<algorithm>
#include<math.h>
const int N=1000;
int a[N];
using namespace std;
 int main()
{
 int n,i,min;	
 scanf("%d",&n);
 for(i=0;i<=n-1;i++)
 {
    scanf("%d",&a[i]);
 }
 sort(a,a+n);
 min=a[1]-a[0];
 for(i=1;i<=n-2;i++)
 {
 	if((a[i+1]-a[i])<min)
 	min=a[i+1]-a[i];
 }
 printf("%d",min);
return 0;
}
