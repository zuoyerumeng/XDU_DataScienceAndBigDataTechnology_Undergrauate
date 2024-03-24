#include<stdio.h>
 int main()
 {
  char str[11][21]={'\0'},t,ch;
  int i,j,k,n,N;
  scanf("%d",&N);
  ch=getchar();
  for(i=1;i<=N;i++)
  {
  	for(j=1;j<=20;j++)
  	{
  		scanf("%c",&str[i][j]);
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
		str[i][j]='\0';
		break;
	} 
  }
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N-1;j++)
		{
			for(k=1;k<=20;k++)
			{
				if(str[j][k]<str[j+1][k])
				    break;
				else if(str[j][k]>str[j+1][k])
				{
					for(n=1;n<=20;n++)
					{
					     t=str[j+1][n];
						 str[j+1][n]=str[j][n];
						 str[j][n]=t;
					 } 
					break;
				}
			 }
		}
	}
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=20;j++)
		{
			if(str[i][j]!='\0')
			    printf("%c",str[i][j]);
			else 
			{
				printf("\n");
				break;
			}
		}
	}
return 0;
}
