#include<stdio.h>
 int main()
 {
  int a,b,c,t,n,s,y;
  scanf("%d",&n);
  for(a=1;a<=9;a++)
  {
  	for(c=0;c<=9;c++)
  	{
  		y=(n-101*(a+c))%20;
  		s=(n-101*(a+c))/20;
  		if(y==0&&s>=0&&s<=9)
  			{
			 b=s;  
			  printf("%d %d %d\n",a,b,c);
		    }
	  }
  }
return 0;
}
