#include<stdio.h>
 int main()
 {
  int a[1000],i,j,sum=0,b[1000];
  for(i=1;i<=1000;i++)
  {
  scanf("%d",&a[i]);
  if(a[i]==0)
  {
  	break;
  }
  else if(a[i]==1)
    sum+=1;
  else if(a[i]==2)
  {
  	b[i]=2;
  	for(j=i-1;j>=1;j--)
  	{
  		if(a[j]==2)
  		  b[i]+=2;
  		else
  		 break;
	  }
	sum+=b[i];
  }
}
  printf("%d",sum);
return 0;
}
