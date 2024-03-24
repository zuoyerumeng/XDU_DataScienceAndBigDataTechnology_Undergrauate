#include<stdio.h>
 int main()
 {
  float i,s,q;
  scanf("%f",&i);
  q=i/10000;
  if(q>=0&&q<=10)
    s=0.1*q;
  else if(q>10&&q<=20)
    s=0.075*q+0.25;
  else if(q>20&&q<=40)
    s=0.05*q+0.75;
  else if(q>40&&q<=60)
    s=0.03*q+1.55;
  else if(q>60&&q<=100)
    s=0.015*q+2.45;
   else if(q>100)
    s=0.01*q+2.95;   
	printf("%.2f",10000*s);
return 0;
}
