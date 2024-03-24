#include<stdio.h>
#include<string.h>
 int main()
 {
  char a[100];
  int b[5]={0},i;
  gets(a);
  int len=strlen(a);
  for(i=0;i<len;i++)
  {
  	if(a[i]>='A'&&a[i]<='Z')
  	    b[0]++;
  	else if(a[i]>='a'&&a[i]<='z')
  	    b[1]++;
  	else if(a[i]==' ')
  	    b[2]++;
  	else if(a[i]>='0'&&a[i]<='9')
  	    b[3]++;
  	else
  	    b[4]++;
  }
  for(i=0;i<=4;i++)
  printf("%d ",b[i]);
return 0;
}
