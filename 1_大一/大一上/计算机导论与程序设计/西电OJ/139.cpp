#include<stdio.h>
 int main()
{
 char c[5],d[5];
 int i;
 for(i=0;i<=3;i++)	
 {
 scanf("%c ",&c[i]);
 d[i]=char(c[i]+4);
 printf("%c",d[i]);
 } 
 scanf("%c",&c[4]);
 d[4]=char(c[4]+4);
 printf("%c",d[4]); 
return 0;
}
