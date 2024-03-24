#include<stdio.h>
 int main()
 {
  int n,i,j,max,sum=0,a[100],b[100],c[100]={0},d[100]; 
  scanf("%d",&n);
  for(i=0;i<=n-1;i++)
  {
  	scanf("%d",&a[i]);
  	b[i]=a[i];
  	while(a[i]!=0)
  	{
  		c[i]+=a[i]%10;
  		a[i]=a[i]/10;
	  }
   }
	 max=c[0];
	 for(j=1;j<=n-1;j++)
	 {
	 	if(c[j]>=max)
	 		max=c[j]; 
	 }
	  for(j=0;j<=n-1;j++)
	  {
	  	if(c[j]==max)
	  	{
	  		d[sum]=b[j];
	  		sum+=1;
		  }
	  }
	  max=d[0];
	  for(j=1;j<sum;j++)
	  {
	  	if(d[j]>max)
	  	  max=d[j];
	  }
  printf("%d",max);
return 0;
}
