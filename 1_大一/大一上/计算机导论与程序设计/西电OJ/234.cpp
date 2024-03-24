#include<stdio.h>
#include<string.h>
 int main()
 {
  int n,i,j,g1[101],g2[101],g3[101];
  float p[101],t2;
  char num[101][10],name[101][10],t1[10],t3[10],xi;
  scanf("%d",&n);
  xi=getchar();
  for(i=1;i<=n;i++)
  {
  	scanf("%s%s%d%d%d",&num[i],&name[i],&g1[i],&g2[i],&g3[i]);
  	xi=getchar();
  	p[i]=(float)(g1[i]+g2[i]+g3[i])/3;
  }
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<n;j++)
  	{
  		if(p[j]<p[j+1]||(p[j]==p[j+1]&&strcmp(num[j],num[j+1])>0))
  		{
  			strcpy(t1,num[j+1]);
  			strcpy(num[j+1],num[j]);
  			strcpy(num[j],t1);
  			t2=p[j+1];
  			p[j+1]=p[j];
  			p[j]=t2;
  			strcpy(t3,name[j+1]);
  			strcpy(name[j+1],name[j]);
  			strcpy(name[j],t3);
		  }
	  }
  }
  for(i=1;i<=n;i++)printf("%s %s %.1f\n",num[i],name[i],p[i]);
return 0;
}
