#include<stdio.h>
 int main()
{
 int n,a[100],b[6]={0},i;
 float p,sum=0;	
 scanf("%d",&n);
 for(i=0;i<=n-1;i++)
 {
 	scanf("%d",&a[i]);
	 sum+=a[i]; 
	if(a[i]>=0&&a[i]<=50)
	   b[0]+=1;
	else if(a[i]>=51&&a[i]<=100)
	   b[1]+=1;
	else if(a[i]>=101&&a[i]<=150)
	   b[2]+=1;
	else if(a[i]>=151&&a[i]<=200)
	   b[3]+=1;
	else if(a[i]>=201&&a[i]<=300)
	   b[4]+=1;
	else if(a[i]>300)
	   b[5]+=1;   
 }
 p=sum/n;
 printf("%.2f\n",p);
 for(i=0;i<=5;i++)
 {
 	printf("%d ",b[i]);
 }
return 0;
}
