#include<stdio.h>
 int main()
 {
  int sum=0,i,s=0;
  char a[1000],b[1000];
  gets(a);
  while (a[sum]!='\0') 
  sum++;
  gets(b);
  while (b[s]!='\0') 
  s++;
  for(i=0;i<sum;i++)
  printf("%c",a[i]);
  for(i=0;i<s;i++)
  printf("%c",b[i]);
return 0;
}

