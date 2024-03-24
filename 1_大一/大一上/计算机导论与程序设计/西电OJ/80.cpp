#include<stdio.h>
#include<string.h>
 int main()
 {
  char ch,c[100],str;
  int i,n,len,sum=0;
  scanf("%c%d",&ch,&n);
  scanf("%s",&c);
  len=strlen(c);
  if(n==1)
  {
  	for(i=0;i<len;i++)
  	{
  		if(c[i]==ch)
  		    sum++;
	  }
  }
  else
  {
  	    if(ch<='Z')
  	       str=char(ch+32);
  	    else
  	       str=char(ch-32);
  	    for(i=0;i<len;i++)
  	  {
  		if(c[i]==ch||c[i]==str)
  		    sum++;
	  }
    }
  printf("%d",sum);
return 0;
}
