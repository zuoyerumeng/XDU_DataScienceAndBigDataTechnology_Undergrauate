#include<stdio.h>
 int main()
 {
  int n,a[1001],i,s,S,t=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  	scanf("%d",&a[i]);
  for(i=1;i<=n;i++)
  {
  	s=0;
  	S=0;
  	for(int j=1;j<=n;j++)
  	{
  		if(a[j]<a[i])
  		  s++;
  		else if(a[j]>a[i])
  		  S++;
	  }
	if(s==S)
	{
		t=1;
		printf("%d",a[i]);
		break;
	}
  }
   if(t==0)
   printf("-1");
 
return 0;
}
