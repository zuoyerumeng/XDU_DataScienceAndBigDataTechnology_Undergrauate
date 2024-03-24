#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
 int main()
 {
  int i,s[100],sum=0,len[100];
  char str[100][101];
  do
  {
  	sum++;
	gets(str[sum]);
  }
  while(str[sum]!="***end***");
  for(i=1;i<sum;i++)
      len[i]=strlen(str[i]);
  sort(len+1,len+sum);
  printf("%d\n",len[sum-1]);
  for(i=1;i<sum;i++)
  {
  	if(strlen(str[i])==len[sum-1])
  	{
  		printf("%s",str[i]);
  		break;
	  }
  }
return 0;
}
