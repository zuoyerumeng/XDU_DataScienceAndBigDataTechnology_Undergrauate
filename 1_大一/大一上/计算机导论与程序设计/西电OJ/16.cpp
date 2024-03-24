#include<stdio.h>
int main()
{
 char a[5],b[5];
 int i;
 for(i=0;i<=4;i++)
 {
     scanf("%c|",&a[i]);
     b[i]=char(a[i]+32);
     printf("%c",b[i]);
 }
    printf("!");
return 0;
}
