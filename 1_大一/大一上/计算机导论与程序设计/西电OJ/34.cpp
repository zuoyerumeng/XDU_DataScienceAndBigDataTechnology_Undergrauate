#include<stdio.h>
 int function(int a,int b);
 int main()
 {
  int a,b;
  scanf("%d%d",&a,&b);
  printf("%d",function(a,b));
return 0;
}
 int function(int a,int b)
 {
 	int t,sum=0,s,T,n;
 	if(a<100&&b<100)
 	  sum=0;
 	else if(a>=100&&b>=100)
 	{
 		if(b<a)
 		{
 		    t=a;
 		    a=b;
 		    b=t;
		 }
		for(int i=a;i<=b;i++)
		{
			int a[5]={0};
			int b[5]={0};
			n=i;
			s=0;
			T=0;
			while(n!=0)
			{
				a[s+1]=n%10;
				b[s+1]=n%10;
				n=n/10;
			    s++;
			}
			for(int j=1;j<=s;j++)
			{
				for(int k=1;k<=s-1;k++)
				{
					 a[j]=a[j]*b[j];
				}
				T+=a[j];
			}
			if(T==i)
			  sum+=1;
		}
	 }
	 else
	 {
	   if(b<a)
 		{
 		    t=a;
 		    a=b;
 		    b=t;
		 }
	   sum=function(100,b);
     }
 return(sum);
 }

