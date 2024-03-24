#include<stdio.h>
#include<math.h>
 int main()
 {
  float x,f;
  scanf("%f",&x);
  if(x>=0)
   f=sqrt(x);
  else
    f=(x+1)*(x+1)+2*x+(float)1/x;
  printf("%.2f",f);
return 0;
}
