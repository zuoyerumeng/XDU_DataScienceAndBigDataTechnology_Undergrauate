#include<stdio.h>
#include<string.h>
 int main()
 {
  int m,n,s[200],a[200],t,i,j;
  char c[200][20],xi,temp[20];
  scanf("%d%d",&m,&n);
  for(i=1;i<=m;i++)
  {
  	scanf("%s%d%d",&c[i],&s[i],&a[i]);
  	xi=getchar();
  }
  for(i=1;i<=m;i++)
  {
  	for(j=1;j<m;j++)
  	{
  		if(s[j]<s[j+1]||(s[j]==s[j+1]&&a[j]<a[j+1])||(s[j]==s[j+1]&&a[j]==a[j+1]&&strcmp(c[j],c[j+1])>0))
  		{
  			strcpy(temp,c[j+1]);
  			strcpy(c[j+1],c[j]);
  			strcpy(c[j],temp);
  			t=s[j+1];
  			s[j+1]=s[j];
  			s[j]=t;
  			t=a[j+1];
  			a[j+1]=a[j];
  			a[j]=t;
		  }
	  }
  }
  for(i=1;i<=n;i++)printf("%s %d %d\n",c[i],s[i],a[i]);
return 0;
}
