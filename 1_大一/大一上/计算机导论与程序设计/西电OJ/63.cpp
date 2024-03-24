#include<stdio.h>
 int main()
 {
  int s,a;
  float t;
  scanf("%d",&s);
  if(s>=0&&s<=3500)
  {
  	t=s;
  	a=0;
  }
  else 
  {
  	a=s-3500;
  	if(a<=1500)
  	t=s-0.03*a;
  	else if(a>1500&&a<=4500)
  	t=105+s-0.1*a;
  	else if(a>4500&&a<=9000)
  	t=555+s-0.2*a;
  	else if(a>9000&&a<=35000)
  	t=1005+s-0.25*a;
  	else if(a>35000)
  	t=2755+s-0.3*a;
  }
  printf("%d",int(t));
return 0;
}
