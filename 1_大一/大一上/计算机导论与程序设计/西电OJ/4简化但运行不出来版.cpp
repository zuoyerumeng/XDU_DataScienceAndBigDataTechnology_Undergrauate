#include<stdio.h>
#include<string.h>
 int main()
 {
  int i,j,k,sum=0,len,c[87],b;
  char str[255],a[88][256],t[256];
  gets(str);
  len=strlen(str);
  for(i=0;i<len;i++)
  {
  	  if(str[i]=='-')
  	{
  		sum++;
  		a[sum][1]='-';
  		b=2;
  		for(j=i+1;j<len;j++)
  		{
  			a[sum][b]=str[j];
  			b++;
  			if(str[j]==' ')
  			{
  				a[sum][b-1]='\0';
				break;
			  }
		  }
    }
  }
	if(sum==0)
      printf("no");	
    else
    {
		for(i=1;i<=sum;i++)
		{
			for(k=i+1;k<=sum;k++)
			{
				if(strcmp(a[i],a[k])==0)
	                strcpy(a[k],a[88]);
	         }
		}      
       for(i=1;i<=sum;i++)
       {
   	        for(j=1;j<sum;j++)
   	        {
   	      	    if(strcmp(a[j],a[j+1])>0)
   	      	    {
   	      	    	strcpy(t,a[j+1]);
   	      	    	strcpy(a[j+1],a[j]);
   	      	    	strcpy(a[j],t);
				 }
		     }
       }

  	    for(i=1;i<=sum;i++)
  		    printf("%s",a[i]);
  }
return 0;
}
