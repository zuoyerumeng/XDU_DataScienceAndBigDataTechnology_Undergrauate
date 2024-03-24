#include<stdio.h>
 int main()
 {
  char c;
  scanf("%c",&c);
  int i,j,n;
  n=c-'A'+1;
	for(i=1;i<=n;i++)
    {
	 for(j=1;j<=(n-i);j++)
     {
	  printf(" ");
     } 
     for(j=1;j<=i;j++)
     {
     	printf("%c",char('A'+j-1));
	 }
	  for(j=i-1;j>=1;j--)
	  {
	  	printf("%c",char('A'+j-1));
	  }
     for(j=1;j<=(n-i);j++)
     {
     	printf(" ");
	 }
	 printf("\n"); 
}
return 0;
}
