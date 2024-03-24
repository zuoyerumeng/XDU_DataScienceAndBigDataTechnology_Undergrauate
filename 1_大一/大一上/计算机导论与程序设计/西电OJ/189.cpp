#include<stdio.h>
 int main()
 {
  int n;
  float h=100,S=100;
  scanf("%d",&n);
  for(int i=1;i<=n;i++)
  {
  	h=h/2;
  	S+=2*h;
  }
  S=S-2*h;
  printf("S=%.3f h=%.3f",S,h);
return 0;
}
