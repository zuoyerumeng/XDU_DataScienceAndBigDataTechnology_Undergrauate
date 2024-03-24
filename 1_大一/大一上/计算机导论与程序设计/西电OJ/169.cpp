#include<stdio.h>
 int main()
 {
  int n,y[101],m[101],d[101],s[101],i,j,t;
  scanf("%d",&n);
  for(i=1;i<=n;i++)scanf("%d/%d/%d%d",&y[i],&m[i],&d[i],&s[i]);
  for(i=1;i<=n;i++)
  {
  	for(j=1;j<n;j++)
  	{
  		if(y[j]<y[j+1]||(y[j]==y[j+1]&&m[j]<m[j+1])||(y[j]==y[j+1]&&m[j]==m[j+1]&&d[j]<d[j+1])||(y[j]==y[j+1]&&m[j]==m[j+1]&&d[j]==d[j+1]&&s[j]<s[j+1]))
  		{
  			t=y[j+1];
  			y[j+1]=y[j];
  			y[j]=t;
  			t=m[j+1];
  			m[j+1]=m[j];
  			m[j]=t;
  			t=d[j+1];
  			d[j+1]=d[j];
  			d[j]=t;
  			t=s[j+1];
  			s[j+1]=s[j];
  			s[j]=t;
		  }
	  }
  }
  for(i=1;i<=n;i++)printf("%d/%d/%d %d\n",y[i],m[i],d[i],s[i]);
return 0;
}
