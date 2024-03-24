#include<stdio.h>
#include<math.h>
 int main()
{
 int i,n,a[30],max;
 scanf("%d",&n);
 for(i=0;i<=n-1;i++)
 {
 	scanf("%d",&a[i]);
 }
 max=abs(a[0]-a[1]);
 for(i=1;i<=n-2;i++)
 {
 	if(abs(a[i]-a[i+1])>max)
 	  max=abs(a[i]-a[i+1]);
 }
 printf("%d",max);
return 0;
}
