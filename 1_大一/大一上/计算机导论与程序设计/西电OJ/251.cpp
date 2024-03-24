#include<stdio.h>
 int main()
 {
  int y,m,d,sum;
  scanf("%d,%d,%d",&y,&m,&d);
  sum=d;
  	switch(m)
  	{
		case 2:sum+=31;break;
  		case 3:sum+=60;break;
  		case 4:sum+=91;break;
  		case 5:sum+=121;break;
  		case 6:sum+=152;break;
  		case 7:sum+=182;break;
  		case 8:sum+=213;break;
  		case 9:sum+=244;break;
  		case 10:sum+=274;break;
  		case 11:sum+=304;break;
  		case 12:sum+=335;break;
	  }
  if((y%4!=0||(y%100==0&&y%400!=0))&&m>2)
     sum--;
  printf("%d",sum);
return 0;
}
