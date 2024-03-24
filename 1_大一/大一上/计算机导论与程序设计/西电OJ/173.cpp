#include<stdio.h>
 int main()
 {
  int n,i,j,k,a[101],l[21],min,f;
  scanf("%d",&n);
  for(i=1;i<=n;i++)scanf("%d",&a[i]);
  for(i=1;i<=20;i++)l[i]=5;
  for(i=1;i<=n;i++)
  {
  	f=0;
	for(j=1;j<21;j++)
  	{
  		if(l[j]>=a[i])
  		{
  			for(k=1;k<=a[i];k++)printf("%d ",5*j-l[j]+k);
  			l[j]-=a[i];
  			printf("\n");
  			f=1;
  			break;
		}
	}
	if(f==0)
	{
		for(j=1;j<21;j++)
  	  {
  		if(a[i]==0)break;
		min=l[j];
  		if(a[i]<min)min=a[i];
		for(k=1;k<=min;k++)
		  {
		  	a[i]--;
		  	printf("%d ",5*j-l[j]+k);
	      }
	    l[j]-=min;
     	}
      printf("\n");
	}
  }
return 0;
}
