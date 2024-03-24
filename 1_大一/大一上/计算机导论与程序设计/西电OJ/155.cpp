#include<stdio.h>
 int main()
 {
  int n,t=1,s=0;
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
  	t=1;
  	for(int j=1;j<=i;j++)
  	{
  		t=t*j;
	  }
	s+=t;
  }
  printf("%d %d %d",n,t,s);
return 0;
}
