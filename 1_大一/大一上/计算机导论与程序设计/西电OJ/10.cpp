#include<stdio.h>
 int main()
{
  int fahr;
  float celsius;
  scanf("%d",&fahr);
  celsius=5.0*(fahr-32)/9;
  printf("%.2f",celsius);
return 0;
}
