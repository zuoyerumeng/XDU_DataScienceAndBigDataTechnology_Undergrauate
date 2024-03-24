#include<stdio.h>
 int main()
 {
  int m;
  scanf("%d",&m);
  for(int i=1;i<=m;i++)
  {
  	printf("%d ",m*(m-1)+2*i-1);
  }
return 0;
}
