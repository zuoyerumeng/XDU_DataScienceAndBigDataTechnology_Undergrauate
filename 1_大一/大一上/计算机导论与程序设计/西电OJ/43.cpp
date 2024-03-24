#include<stdio.h>
 int main()
{
 int i,n,p=0,min,max,a[9];
 scanf("%d",&n);
 if(n==0)printf("1 0 0");
 else
{
 while(n!=0)
 {
    a[p]=n%10;
    n=n/10;
    p++;
 }
 min=a[0];
 max=a[0];
 for(i=1;i<p;i++)
 {
 	if(a[i]>max)max=a[i];
 	if(a[i]<min)min=a[i]; 
 }
 printf("%d %d %d",p,max,min);
}
return 0;
}
