#include<stdio.h>
 int main()
 {
  char s[50];
  int i,sum=0,a1=0,a2=0,b1=0,b2=0,c1=0,c2=0,f;
  gets(s);
  while(s[sum]!='\0')sum++;
  f=1;
  for(i=0;i<sum;i++)
  {
  	switch(s[i])
  	{
  		case '(':a1++;break;
  		case ')':a2++;break;
  		case '[':b1++;break;
  		case ']':b2++;break;
  		case '{':c1++;break;
  		case '}':c2++;break;
	  }
	if(a1<a2||b1<b2||c1<c2)
	{
		f=0;
		break;
	}
  }
  if(a1!=a2||b1!=b2||c1!=c2)f=0;
  if(f==1)printf("yes");
  else printf("no");
return 0;
}
