#include<stdio.h>
 int main()
 {
  int n,i,d1,d2,d3;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	d1=i%10;
  	d2=i/10%10;
  	d3=i/100%10;
  	if(i+d1*100+d2*10+d3==n)
  	    printf("%d %d %d\n",d3,d2,d1);
  }
return 0;
}
