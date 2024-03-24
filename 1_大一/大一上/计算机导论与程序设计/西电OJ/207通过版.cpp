#include<stdio.h>
#include<string.h>
 int main()
 {
  int n,i,j;
  char a[10][20],b[20];
  scanf("%d",&n);
  for(i=1;i<=n;i++)
      scanf("%s",&a[i]);
   for(i=1;i<=n;i++)
   {
   	    for(j=1;j<=n-1;j++)
   	    {
			if(strcmp(a[j],a[j+1])>0)
   	    	{
   	    		strcpy(b,a[j]);
   	    		strcpy(a[j],a[j+1]);
   	    		strcpy(a[j+1],b);
			   }
		   }
	} 
  for(i=1;i<=n;i++)
    printf("%s\n",a[i]);
return 0;
}
