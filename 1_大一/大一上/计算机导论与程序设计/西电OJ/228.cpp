#include<stdio.h>
 int main()
 {
  int sum=0,i,z=0,s=0,j=0;
  char a[1000];
  gets(a);
  while (a[sum]!='\0') 
  sum++;
  for(i=0;i<sum;i++)
  {
  	if(i%2==0)
  	 printf("%c",a[i]);
}
return 0;
}
