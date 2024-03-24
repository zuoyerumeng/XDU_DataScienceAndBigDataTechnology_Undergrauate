#include<stdio.h>
#include<math.h>
 int main()
 {
  int n;
  double sum=0.0;
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
  	sum+=((double)i/(double)(2*i-1))*pow(-1.0,(double)(i+1));
  }
  printf("%.3lf",sum);
return 0;
}
