#include<stdio.h>
 int main()
 {
  int n,a[1001],b[1001]={0},c[1001],i,j,t;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d",&c[i]);
  	a[i]=c[i];
  	while(c[i]!=0)
  	{
  		b[i]+=c[i]%10;
  		c[i]=c[i]/10;
	  }
  }
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<=n;j++)
  	{
  		if(b[j]<b[j+1])
  		{
  			t=b[j];
  			b[j]=b[j+1];
  			b[j+1]=t;
  			t=a[j];
  			a[j]=a[j+1];
  			a[j+1]=t;
		  }
		if(b[j]==b[j+1])
  		{
  			if(a[j]>a[j+1])
  			{
  				t=b[j];
  			    b[j]=b[j+1];
  			    b[j+1]=t;
  			    t=a[j];
  			    a[j]=a[j+1];
  		        a[j+1]=t;
			  }
			
		  } 
	  }
  }
  for(i=1;i<=n;i++)
    printf("%d %d\n",a[i],b[i]);
return 0;
}
