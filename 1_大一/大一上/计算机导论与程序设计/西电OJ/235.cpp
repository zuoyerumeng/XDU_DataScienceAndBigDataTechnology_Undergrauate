#include<stdio.h>
 int main()
 {
  int n;
  scanf("%d",&n);
  if(n<1||n>12)
    printf("wrong");
  else
  {
  	switch(n)
  	{
  		case 1:printf("Janurary");break;
  		case 2:printf("Febrary");break;
  		case 3:printf("March");break;
  		case 4:printf("April");break;
  		case 5:printf("May");break;
  		case 6:printf("June");break;
  		case 7:printf("July");break;
  		case 8:printf("August");break;
  		case 9:printf("Semptember");break;
  		case 10:printf("October");break;
  		case 11:printf("November");break;
  		case 12:printf("December");break;
	  }
  }
return 0;
}
