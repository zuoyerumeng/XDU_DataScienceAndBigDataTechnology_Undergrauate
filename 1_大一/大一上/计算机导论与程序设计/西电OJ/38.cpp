#include<stdio.h>
 int main()
 {
  int n,a[9],i=1,sum=0,s=0,t=0;
  scanf("%d",&n);
  while (n!=0)
  {
  	a[i]=n%10;
  	n=n/10;
  	i++;
  	sum++;
  }
  for(i=1;i<=sum/2+1;i++)
  {
  	if(a[i]!=a[sum+1-i])
  	   s++;
  }
  if(s==0)
  {
  	for(i=1;i<=sum;i++)
  	  t+=a[i];
  	  printf("%d",t); 
  }
  else
    printf("no");
return 0;
}
