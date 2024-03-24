#include<stdio.h>
 int main()
 {
  int sum=0,i;
  char a[1000];
  gets(a);
  while (a[sum]!='\0') 
  sum++;
  for(i = sum-1; i >= 0; i--)
  printf("%c",a[i]);
return 0;
}
