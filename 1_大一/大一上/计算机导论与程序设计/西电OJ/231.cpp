 #include<stdio.h>
 #include<string.h>
 int main()
 {
  char str[100][20];
  int i,j,max,S=0,len[101];
  for(i=1;i<=100;i++)
  {
  	for(j=0;j<20;j++)
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
		S=i;
		str[i][j]='\0';
		break;
	}  
  }
  for(i=1;i<=S;i++)
     len[i]=strlen(str[i]);
  len[S]--;
  max=len[1];
  for(i=2;i<=S;i++)
  {
  	if(len[i]>max)
  	    max=len[i];
  }
  printf("%d",max);
return 0;
}
