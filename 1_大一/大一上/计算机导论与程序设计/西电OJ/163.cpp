#include<stdio.h>
 int main()
 {
  int n,a[21][21],i,j,sum=0;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<=n;j++)
  	scanf("%d",&a[i][j]);
  }
  for(i=1;i<=n;i++)
      sum+=a[i][i]+a[i][n+1-i];
  if(n%2==1)
    sum-=a[(n+1)/2][(n+1)/2];
  printf("%d",sum);
return 0;
}
