#include<stdio.h>
 int main()
{
 int y,n,d;	
 scanf("%d%d",&n,&y);
 if(y>=1&&y<=12)
 d=(y==1||y==3||y==5||y==7||y==8||y==10||y==12)?31:(y==2&&(n%4!=0||(n%100==0&&n%400!=0)))?28:(y==4||y==6||y==9||y==11)?30:29;
 printf("%d",d);
return 0;
}
