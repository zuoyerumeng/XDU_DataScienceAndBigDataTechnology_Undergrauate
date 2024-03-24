#include<stdio.h>
 int main()
 {
  char a[13];
  int i,sum=0,s=0;
  gets(a);
  for(i=0;i<11;i++)
  {
  	if(a[i]!='-')
  	{
  		s++;
  		sum+=s*(a[i]-'0');
	  }
  }  
  if(sum%11!=10)
  {
  	if(sum%11==a[12]-'0')
  	    printf("Right");
    else
    {
    	a[12]=char('0'+sum%11);
    	puts(a);
	}
  }
  else
  {
  	if(a[12]=='X')
  	    printf("Right");
    else
    {
    	a[12]='X';
    	puts(a);
	}
  }
return 0;
}
