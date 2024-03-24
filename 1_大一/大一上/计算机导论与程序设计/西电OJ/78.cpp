#include<stdio.h>
 int main()
 {
  int n,m,x,y=1,i,j,sum=0,f[21][21]={0};
  char c[21][21],xi[21];
  scanf("%d%d%d",&n,&m,&x);
  xi[0]=getchar(); 
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<=m;j++)
  	    scanf("%c",&c[i][j]);
  	xi[i]=getchar();
  }
  do
  {
  	sum++;
  	f[y][x]=1;
  	switch(c[y][x])
  	{
  		case 'N':y--;break;
  		case 'S':y++;break;
  		case 'E':x++;break;
  		case 'W':x--;break;
	  }
  }
  while(f[y][x]==0&&x!=0&&y!=0&&x!=m+1&&y!=n+1);
  if(f[y][x]==1)
     printf("loop %d",sum,x,y);
  else
     printf("out %d %d %d",sum,x,y);
return 0;
}
