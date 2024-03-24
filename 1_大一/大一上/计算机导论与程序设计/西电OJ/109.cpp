#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
 int main()
 {
  char a[100],b[100];
  int i,len,sum=0,s;
  gets(a);
  len=strlen(a);
  for(i=1;i<len;i++)
  {
  	if(a[i]>a[0])
  	{
  		sum++;
  		b[sum]=a[i];
	  }
  }
  sum++;
  b[sum]=a[0];
  s=sum;
  for(i=1;i<len;i++)
  {
  	if(a[i]<=a[0])
  	{
  		sum++;
  		b[sum]=a[i];
	  }
  }
  sort(b+s+1,b+len+1);
  for(i=1;i<=len;i++)
    printf("%c",b[i]);
return 0;
}
