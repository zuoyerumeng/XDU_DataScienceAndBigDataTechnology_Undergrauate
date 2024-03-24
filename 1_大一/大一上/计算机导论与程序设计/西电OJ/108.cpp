#include<stdio.h>
#include<string.h>
#include<math.h>
 int main()
 {
  char c[100];
  int i,l,f=0,flag=0,sum=0,n=0,max;
  gets(c);
  l=strlen(c);
  for(i=l-1;i>=0;i--)
  {
  	if(c[i]>='0'&&c[i]<='9')
  	{
  		f=1;
  		n+=(c[i]-'0')*(double)pow(10.0,(double)sum);
  		sum++;
	  }
  }
  if(f==0||n==0)
     printf("0");
  else
  {
  	for(i=2;i<n;i++)
  	{
  		if(n%i==0)
  		{
  			flag=1;
  			max=i;
		  }
	  }
	if(flag==0)
	    printf("%d",n);
	else
	    printf("%d",max);
  }
return 0;
}
