#include<stdio.h>
#include<string.h>
 int main()
 {
  char a[50];
  int i,len,f=1;
  gets(a);
  len=strlen(a);
  for(i=0;i<len;i++)
  {
  	if(a[i]!=a[len-1-i])
  	{
  		f=0;
  		break;
	  }
  }
  if(f==1)
     printf("yes");
  else
     printf("no");
return 0;
}
