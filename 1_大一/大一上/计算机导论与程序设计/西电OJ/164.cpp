#include<stdio.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int i,s=0,sum=0;
  char str[81],c[81];
  gets(str);
  while(str[sum]!='\0')
      sum++;
 for(i=sum;i>0;i--)
     str[i]=str[i-1];
  for(i=1;i<=sum;i++)
  {
  	if(str[i]>='a'&&str[i]<='z')
  	    str[i]=char(str[i]-32);
  }
  for(i=1;i<=sum;i++)
  {
  	if(str[i]>='A'&&str[i]<='Z')
  	{
  		s++;
  		c[s]=str[i];
	  }
  }
  sort(c+1,c+s+1);
  s=0;
for(i=1;i<=sum;i++)
{
	if(str[i]>='A'&&str[i]<='Z')
	{
		s++;
		str[i]=c[s];
	}
}
  for(i=1;i<=sum;i++)
  printf("%c",str[i]);
return 0;
}
