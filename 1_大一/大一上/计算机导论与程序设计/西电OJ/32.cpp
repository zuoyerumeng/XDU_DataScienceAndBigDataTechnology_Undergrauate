#include<stdio.h>
 int main()
{
 int n,sum=0;
 scanf("%d",&n);
 while(n!=1)
 {
 	 sum+=1;
	 if(n%2==0)
 	  n=n/2;
 	else 
 	  n=3*n+1;
 }
 printf("%d",sum);
return 0;
}
