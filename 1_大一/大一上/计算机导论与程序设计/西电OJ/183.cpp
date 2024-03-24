#include<stdio.h>
 int main()
 {
  int a,b,c=1,d,e;
  scanf("%d%d",&a,&b);
  d=a;
  e=b;
  while(c!=0)
 {
 	c=a%b;
 	a=b;
 	b=c;
 }
 printf("%d ",a);
  printf("%d",d*e/a);
return 0;
}
