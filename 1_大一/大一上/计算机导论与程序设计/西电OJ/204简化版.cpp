#include<stdio.h>//����汾����ż�����ǻ��е����⣬��������ǿ���QAQ 
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

