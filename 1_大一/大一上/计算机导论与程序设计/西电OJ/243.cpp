#include<stdio.h>
#include<string.h>
 int main()
 {
  char name[100][20],t1[20];
  int n,i,j,g[7][100],sum[100]={0},xi,t2; 
  scanf("%d",&n);
  xi=getchar();
  for(i=1;i<=n;i++)
  {
  	scanf("%s%d%d%d%d%d%d",&name[i],&g[1][i],&g[2][i],&g[3][i],&g[4][i],&g[5][i],&g[6][i]);
    for(j=1;j<7;j++)sum[i]+=g[j][i];
  }
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<n;j++)
  	{
  		if(sum[j]<sum[j+1]||(sum[j]==sum[j+1]&&g[6][j]<g[6][j+1]))
  		{
  			strcpy(t1,name[j+1]);
  			strcpy(name[j+1],name[j]);
  			strcpy(name[j],t1);
  			t2=sum[j+1];
  			sum[j+1]=sum[j];
  			sum[j]=t2;
  			t2=g[6][j+1];
  			g[6][j+1]=g[6][j];
  			g[6][j]=t2;
		  }
	  }
  }
 for(i=1;i<=n;i++)printf("%s %d %d\n",name[i],sum[i],g[6][i]);
return 0;
}
