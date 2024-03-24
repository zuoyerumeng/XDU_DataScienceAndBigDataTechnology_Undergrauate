#include<stdio.h>
 int main()
 {
  char str[51];
  int n,i,sum=0,s,S,a[51]={0};
  for(i=1;i<51;i++)
  {
	scanf("%c",&str[i]);
  	if(str[i]=='\n')
  	{
  		s=i-1;
		break;
	  }
  	else if(str[i]!=' ')
  	    a[i]=1;
  }
  scanf("%d",&n);
  for(i=1;i<51;i++)
  {
  	sum+=a[i];
  	if(sum==n)
  	{
  		S=i;
  		break;
	  }
  }
  for(i=S+1;i<=s;i++)
      printf("%c",str[i]);
  return 0;
}
