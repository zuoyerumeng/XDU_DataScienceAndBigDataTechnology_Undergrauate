#include<stdio.h>
#include<algorithm>
 int main()
{
 int a,b,i,j,k;	
 scanf("%d%d",&a,&b);
 for(i=a;i<=b;i++)
 {
	 k=i;
	 for(j=1;j<=i-1;j++)
 	{
 		if(i%j==0)
 		  k=k-j;
	 }
	 if(k==0)
	 printf("%d\n",i);    
 }
return 0;
}
