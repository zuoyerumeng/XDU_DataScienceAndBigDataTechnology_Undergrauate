#include<stdio.h>
 int main()
 {
  int m,n,a=0,b=0,c=0,d=0;
  scanf("%d%d",&m,&n);
  for(int i=1;i<m;i++)
  {
  	if(m%i==0)
  	{
  	a+=i;
  	c++;
    }
  }
  for(int i=1;i<n;i++)
  {
  	if(n%i==0)
  	{
  	b+=i;
  	d++;
    }
  }
  if(a==n&b==m)
   printf("yes "); 
  else
   printf("no ");
  printf("%d %d",c,d);
return 0;
}
