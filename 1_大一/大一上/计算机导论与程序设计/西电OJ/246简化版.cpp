#include<stdio.h>
#include<string.h>
#include<ctype.h>
 int main()
 {
  char str[101][9],w[9],c[100];
  int i,sum=1,l,s=0;
  gets(c);
  gets(w);
  printf("%s",w);
  l=strlen(c);
  for(i=0;i<l;i++)
      c[i]=toupper(c[i]);
  for(i=0;i<strlen(w);i++)
      w[i]=toupper(w[i]);
  for(i=0;i<l;i++)
  {
	if(c[i]!=' ')
  		str[sum][strlen(str[sum])]=c[i];
	else
	    sum++; 
  }
  for(i=1;i<=sum;i++)
  {
  	if(strcmp(str[i],w)==0)
  	    s++;
  }	  
  printf(" %d",s);
return 0;
}

