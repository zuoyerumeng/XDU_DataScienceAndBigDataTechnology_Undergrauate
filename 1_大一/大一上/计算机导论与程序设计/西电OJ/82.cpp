#include<stdio.h>
 int main()
 {
  int i,s=0,sum=0,S=0;
  char a[50];
  gets(a);
  while(a[s]!='\0')
  	s++;
  if(s==0)
      sum=0;
  else
  {
  	sum++;
  	if(s>8)
  	    sum++;
  	for(i=0;i<s;i++)
  	{
  		if(a[i]>='a'&&a[i]<='z')
  		{
  			S++;
  			break;
		  }
	  }
	for(i=0;i<s;i++)
  	{
  		if(a[i]>='A'&&a[i]<='Z')
  		{
  			S++;
  			break;
		  }
	  }
	for(i=0;i<s;i++)
  	{
  		if(a[i]>='0'&&a[i]<='9')
  		{
  			S++;
  			break;
		  }
	  }
	for(i=0;i<s;i++)
  	{
  		if(a[i]<'0'||(a[i]>'9'&&a[i]<'A')||(a[i]>'Z'&&a[i]<'a')||a[i]>'z')
  		{
  			S++;
  			break;
		  }
	  }
	   switch(S)
	   {
	   	case 1:break;
		case 2:sum+=1;break;
	   	case 3:sum+=2;break;
	   	case 4:sum+=3;break;
	   }
  }
  printf("%d",sum);
return 0;
}
