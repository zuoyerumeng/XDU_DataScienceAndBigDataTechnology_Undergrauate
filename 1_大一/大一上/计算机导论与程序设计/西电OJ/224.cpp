#include<stdio.h>
 int main()
 {
  int a[3][4],b[4][3],c[3][3]={0},i,j,k;
  for(i=1;i<3;i++)
  {
  	for(j=1;j<4;j++)
  		scanf("%d",&a[i][j]);
  }  
  for(i=1;i<4;i++)
  {
  	for(j=1;j<3;j++)
  		scanf("%d",&b[i][j]); 	    
  }
  for(i=1;i<3;i++)
  {
  	for(j=1;j<3;j++)
  	{
  		for(k=1;k<=3;k++)
  		    c[i][j]+=a[i][k]*b[k][j];
  		printf("%d ",c[i][j]); 
	  }
	printf("\n");
  }
return 0;
}
