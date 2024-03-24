#include<stdio.h>
#include<ctype.h>
#include<string.h>
 int main()
 {
  char str[3][100];
  int len1,len2,i,j,max=0,sum=0;
  scanf("%s",&str[1]);
  scanf("%s",&str[2]);
  len1=strlen(str[1]);
  len2=strlen(str[2]);
  for(i=0;i<len1;i++)
      str[1][i]=toupper(str[1][i]);
 for(i=0;i<len2;i++)
      str[2][i]=toupper(str[2][i]);
  for(i=0;i<len1;i++)
  {
  	for(j=0;j<len2;j++)
  	{
  		if(str[1][i]==str[2][j])
  		{
  			sum=1;
			while(str[1][i+sum]==str[2][j+sum]&&i+sum<len1&&j+sum<len2)
  			    sum++;
  			if(sum>max)
  			    max=sum;
		  }
	  }
  }
  printf("%.3f",2*(float)max/(len1+len2));
return 0;
}
