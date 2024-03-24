#include<stdio.h>
#include<string.h>
#include<math.h>
 int main()
 {
  char str[4][8],t[8];
  int i,j,len1,len2,a=0,b=0,c,temp;
  for(i=1;i<=3;i++)
  	scanf("%s",&str[i]);
  for(i=1;i<=3;i++)
  {
  	for(j=1;j<3;j++)
  	{
  		if(strcmp(str[j],str[j+1])>0)
  		{
  			strcpy(t,str[j+1]);
  			strcpy(str[j+1],str[j]);
  			strcpy(str[j],t);
		  }
	  }
  }
  len1=strlen(str[2]);
  len2=strlen(str[3]);
  for(i=0;i<len1;i++)
  	  a+=(str[2][i]-'0')*(double)pow(10.0,(double)(len1-i-1));
  for(i=0;i<len2;i++)
  	  b+=(str[3][i]-'0')*(double)pow(10.0,(double)(len2-i-1));
 if(a>b)
 {
 	temp=a;
 	a=b;
 	b=temp;
 }
  switch(str[1][0])
  {
  	case'+':c=a+b;break;
  	case'-':c=b-a;break;
  	case'*':c=a*b;break;
  	case'/':c=b/a;break;
  	case'%':c=b%a;break;
  }
  printf("%d",(int)c);
return 0;
}
