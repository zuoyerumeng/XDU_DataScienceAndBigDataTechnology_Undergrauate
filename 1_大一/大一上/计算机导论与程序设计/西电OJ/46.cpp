#include<stdio.h>
 int main()
{
 int n,a[100],i,sum=0,m=0;	
 scanf("%d",&n);
 for(i=0;i<n;i++)
 {
 	scanf("%d",&a[i]);
 }
  for(i=0;i<n;i++)
  {
  	if(a[i]==a[i+1])
  	  m+=1;
  }
  if(m==0)
  {
  	 for(i=1;i<=n-2;i++)
  	 {
  	 	if((a[i]>a[i-1]&&a[i]>a[i+1])||(a[i]<a[i-1]&&a[i]<a[i+1]))
  	 	  {
			sum+=1;
		  }
	   }
  printf("%d",sum);
  } 
return 0;
}
