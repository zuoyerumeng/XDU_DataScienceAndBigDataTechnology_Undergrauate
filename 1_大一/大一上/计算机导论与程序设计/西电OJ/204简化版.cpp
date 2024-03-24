#include<stdio.h>//这个版本好像偶尔还是会有点问题，请求大佬们看看QAQ 
#include<string.h>
 int main()
 {
  char str[101][9],w[9],c[100];
  int i,sum=1,l,s=0;
  gets(c);
  gets(w);
  printf("%s",w);
  l=strlen(c);
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

