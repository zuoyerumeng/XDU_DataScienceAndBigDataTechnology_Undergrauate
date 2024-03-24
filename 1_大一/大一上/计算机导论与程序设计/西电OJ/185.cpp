#include<stdio.h>
#include<math.h>
 int main()
 {
  double x,y,a;
  scanf("%lf",&a);
  x=a;
  y=a;
  do
  {
  	x=y;
	y=(x+(double)(a/x))/2;
  }
  while(fabs(y-x)>=0.00001);
  printf("%.5lf",y);
return 0;
}
