#include<stdio.h>
 int main()
 {
  int n,a[11],i,min,max,sum=0;
  float p;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&a[i]);
  	sum+=a[i]; 
  }
  min=a[1];
  max=a[1];
  for(i=2;i<=n;i++)
  {
  	if(a[i]>max)
  	    max=a[i];
  }
    for(i=2;i<=n;i++)
    {
    	if(a[i]<min)
    	    min=a[i];
	}
	sum-=min+max;
	p=(float)sum/(n-2);
  printf("%.2f",p);
return 0;
}
