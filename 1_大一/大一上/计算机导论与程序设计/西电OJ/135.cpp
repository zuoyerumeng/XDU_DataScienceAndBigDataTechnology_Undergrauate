#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
 int main()
 {
  char c[100];
  int i,j,l,n[100]={0},p,sum=0;
  gets(c);
  l=strlen(c);
  for(i=l-1;i>=0;i--)
  {
	  if(c[i]>='0'&&c[i]<='9'&&(c[i+1]<'0'||c[i+1]>'9'))
  	{
  		sum++;
		p=0;
		j=i;
		while(c[j]>='0'&&c[j]<='9')
		{
			n[sum]+=(c[j]-'0')*(double)pow(10.0,(double)p);
  		    p++;
  		    j--;
		}
	  }
  }
  sort(n+1,n+sum+1);
  for(i=sum;i>0;i--)
      printf("%d ",n[i]);
return 0;
}
