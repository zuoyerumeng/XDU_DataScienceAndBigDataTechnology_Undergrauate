#include<stdio.h>
 int main()
 {
  char c;
  float sum,n,cha;
  scanf("%f",&n);
  if(n>=0&&n<=110)
  {
  	sum=n/2;
  	c='A';
  	cha=0.00;
  }
  else if(n>110&&n<=210)
    {
    	sum=0.55*(n-10);
    	c='B';
    	cha=n-110;
	}
   else if(n>210)
    {
    	sum=0.7*n-37;
    	c='C';
    	cha=n-210;
	}
  printf("%.2f %c %.2f",sum,c,cha);
return 0;
}
