#include<stdio.h>
 int main()
 {
  int i,j,s[100],max,t=0,S,m;
  char str[100][101];
  for(i=1;i<=100;i++)
  {
  	for(j=1;j<=100;j++)
  	{
  		scanf("%c",&str[i][j]);
  		if(str[i][j]=='\n') 
  		{
  			s[i]=j-1;
  			str[i][j]='\0';
  			break;
		  }
		else if(str[i][j]=='*')	
		 {
		 	t=1;
		 	break;
		  }   
	  }
	if(t==1)
	{
		S=i-1;
		break;
	}  
   }
   max=s[1];
   m=1;
   for(i=2;i<=S;i++)
   {
   	  if(s[i]>max)
   	  {
   	  	  max=s[i];
   	  	  m=i;
		}  
   }
  printf("%d\n",max);
  for(i=1;i<=max;i++)
      printf("%c",str[m][i]);
return 0;
}
