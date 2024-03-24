#include<stdio.h>
#include<ctype.h>
 int main()
 {
  char str[101][9]={'\0'},word[9]={'\0'};
  int i,j,sum=0,S=0,t=0;
  for(i=1;i<=100;i++)
  {
  	for(j=1;j<=8;j++)
  	{
  		scanf("%c",&str[i][j]);
  		str[i][j]=toupper(str[i][j]);
  		if(str[i][j]==' ')
  		{
  			str[i][j]='\0';
			break;
		  }  
  		else if(str[i][j]=='\n') 
			break;
	  }
	if(str[i][j]=='\n')
	{
		S=i;
		str[i][j]='\0';
		break;
	}  
  }
  for(j=1;j<=8;j++)
{
	scanf("%c",&word[j]);
	if(word[j]!='\n')
	{
		printf("%c",word[j]);
        word[j]=toupper(word[j]);
	}
    else
    {
       word[j]='\0';
       break;
	}
}
printf(" ");
  for(i=1;i<=S;i++)
  {
  	t=0;
		for(j=1;j<=8;j++)
  	  {
  	  	if(str[i][j]!=word[j])
  	  	{
  	  		t=1;
  	  		break;
		 }
		}
	if(t==0)
	    sum++;
  }	  
  printf("%d",sum);
return 0;
}

