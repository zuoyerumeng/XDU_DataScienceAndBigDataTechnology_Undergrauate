#include<stdio.h>
 int main()
 {
  char c;
  int n;
  scanf("%c%d",&c,&n);
  int i,j;
  for(i=1;i<=n;i++)
    {
	 for(j=1;j<=(n-i);j++)
     {
	  printf(" ");
     } 
     for(j=1;j<=i;j++)
     {
     	printf("%c ",c);
	 }
    	printf("\n"); 
	 }
return 0;
}
