#include<stdio.h>
 int main()
 {
  int y,d;
  scanf("%d%d",&y,&d);
  if(y%4!=0||(y%100==0&&y%400!=0))
  {
  	if(d>=1&&d<=31)
  	 printf("1 %d",d);
  	else if(d>=32&&d<=59)
  	 printf("2 %d",d-31);
  	else if(d>=60&&d<=90)
  	 printf("3 %d",d-59);
  	else if(d>=91&&d<=120)
  	 printf("4 %d",d-90);
  	else if(d>=121&&d<=151)
  	 printf("5 %d",d-120);
  	else if(d>=152&&d<=181)
  	 printf("6 %d",d-151);
  	else if(d>=182&&d<=212)
  	 printf("7 %d",d-181);
  	else if(d>=213&&d<=243)
  	 printf("8 %d",d-212);
  	else if(d>=244&&d<=273)
  	 printf("9 %d",d-243);
  	else if(d>=274&&d<=304)
  	 printf("10 %d",d-273);
  	else if(d>=305&&d<=334)
  	 printf("11 %d",d-304);
  	else if(d>=335&&d<=365)
  	 printf("12 %d",d-334);
  }
  else
  {
  	if(d>=1&&d<=31)
  	 printf("1 %d",d);
  	else if(d>=32&&d<=60)
  	 printf("2 %d",d-31);
  	else if(d>=61&&d<=91)
  	 printf("3 %d",d-60);
  	else if(d>=92&&d<=121)
  	 printf("4 %d",d-91);
  	else if(d>=122&&d<=152)
  	 printf("5 %d",d-121);
  	else if(d>=153&&d<=182)
  	 printf("6 %d",d-152);
  	else if(d>=183&&d<=213)
  	 printf("7 %d",d-182);
  	else if(d>=214&&d<=244)
  	 printf("8 %d",d-213);
  	else if(d>=245&&d<=274)
  	 printf("9 %d",d-244);
  	else if(d>=275&&d<=305)
  	 printf("10 %d",d-274);
  	else if(d>=306&&d<=335)
  	 printf("11 %d",d-305);
  	else if(d>=336&&d<=366)
  	 printf("12 %d",d-335);
  }
return 0;
}
