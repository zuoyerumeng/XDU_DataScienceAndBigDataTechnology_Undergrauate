#include<stdio.h>
 int main()
{
 int n,a[4],max,i;
 for(i=0;i<=3;i++)
 {
 	scanf("%d",&a[i]);
 }	
 max=a[0];
  for(i=1;i<=3;i++)
 {
 	if(a[i]>max)
 	 max=a[i];
 }
 printf("%d",max);
return 0;
}
