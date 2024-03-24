#include<stdio.h>
 int main()
 {
  int sum=0,i,z=0,s=0;
  char a[1000];
  gets(a);
  while (a[sum]!='\0') 
  sum++;
  for(i=0;i<sum;i++)
  {
  	if(a[i]>='0'&&a[i]<='9')
  	s++;
  	else if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z'))
  	z++;
  }
  printf("%d,%d",z,s);
return 0;
}
