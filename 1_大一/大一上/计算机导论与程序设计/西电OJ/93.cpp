#include<stdio.h>
 int main()
 {
  int a,b,t;
  scanf("%d%d",&a,&b);
  if(a<b)
  {
  	t=a;
	a=b;
	b=t;
  }
  printf("%d %d",a%10,b*b);
return 0;
}
