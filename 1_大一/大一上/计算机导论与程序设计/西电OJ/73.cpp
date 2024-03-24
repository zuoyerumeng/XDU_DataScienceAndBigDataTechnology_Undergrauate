#include<stdio.h>
 int main()
 {
  char a[50],b[50];
  int i,j,k,s=0,sum=0,t=0,c[25]={0};
  gets(a);
  while(a[sum]!='\0')
    sum++;
  for(i=0;i<sum;i++)
  {
  	if((a[i]>='a'&&a[i]<='z')||(a[i]>='A'&&a[i]<='Z'))
  	{
  		s++;
  		b[s]=a[i];
		if(a[i+1]>='0'&&a[i+1]<='9')
	  {
	     if(a[i+2]>='0'&&a[i+2]<='9')
	        c[s]=10*(a[i+1]-'0')+(a[i+2]-'0');
	     else
	        c[s]=a[i+1]-'0';
	  }
        else
	        c[s]=1;
	}
  }
  for(i=1;i<=s;i++)
  {
  	for(j=1;j<=c[i];j++)
  	    printf("%c",b[i]);
  }
  printf("\n");
return 0;
}
