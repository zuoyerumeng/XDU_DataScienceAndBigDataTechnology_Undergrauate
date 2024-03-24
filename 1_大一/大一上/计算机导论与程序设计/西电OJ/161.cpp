#include<stdio.h>
 int main()
 {
  int n,a=0,b=0,c=0,d=0,e=0;
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
  	if(i%2==0)
  	b++;
  	else
  	a++;
  }
  for(int i=1;i<=n;i++)
  {
  	if(i%3==0)
  	c++;
  }
  for(int i=1;i<=n;i++)
  {
  	if(i%5==0)
  	d++;
  }
  for(int i=1;i<=n;i++)
  {
  	if(i%7==0)
  	e++;
  }
  printf("%d %d %d %d %d",a,b,c,d,e);
return 0;
}
