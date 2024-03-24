#include<stdio.h>
 int main()
 {
  int a[6][5],f[6]={0},flag[6]={0},i,j,s=0,S=0,sum[6]={0},t=0;
  for(i=1;i<=5;i++)
  {
  	for(j=1;j<=4;j++)
  	{
  	    scanf("%d",&a[i][j]);
  	    sum[i]+=a[i][j];
  	    if(a[i][j]<60)
  	        f[i]++;
  	    else if(a[i][j]>=85)
  	        flag[i]++;
    }
    if(f[i]>=2)
       s++;
    if(sum[i]>=360||flag[i]==4)
       S++;
  }
 for(i=1;i<=5;i++)
   t+=a[i][1];
  printf("%.1f %d %d",(float)t/5,s,S);
return 0;
}
