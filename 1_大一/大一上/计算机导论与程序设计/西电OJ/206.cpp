#include<stdio.h>
 int main()
 {
  int i,s[51],sum=0;
  char str[51],ch;
  for(i=1;i<51;i++)
  {
	scanf("%c",&str[i]);
  	if(str[i]=='\n')
  	    break;
  	sum++;
  }
  scanf("%c",&ch);
  for(i=1;i<=sum;i++)
  {
    if(str[i]=='\n')
        break;
	else if(str[i]!=ch)	
	   printf("%c",str[i]);     
  }
return 0;
}
