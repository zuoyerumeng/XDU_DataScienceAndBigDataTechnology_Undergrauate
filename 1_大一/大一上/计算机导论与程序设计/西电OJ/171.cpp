#include<stdio.h>
 int main()
 {
  int n,i,j,m[101],h1[101],h2[101],m1[101],m2[101],l[101],num[201]={0},sum=0,f,t;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
  	scanf("%d%d:%d%d:%d",&m[i],&h1[i],&m1[i],&h2[i],&m2[i]);
  	f=1;
  	for(j=1;j<=sum;j++)
  	{
  		if(m[i]==num[j])
  		{
  			l[j]+=60*(h2[i]-h1[i])+m2[i]-m1[i];
			f=0;
  			break;
		  }
	  }
	if(f==1)
	{
		sum++;
		num[sum]=m[i];
		l[j]=60*(h2[i]-h1[i])+m2[i]-m1[i];
    }
  }
  for(i=1;i<=sum;i++)
  {
  	for(j=1;j<sum;j++)
  	{
  		if(l[j]<l[j+1]||(l[j]==l[j+1]&&num[j]>num[j+1]))
  		{
  			t=num[j+1];
  			num[j+1]=num[j];
			num[j]=t;
			t=l[j+1];
			l[j+1]=l[j];
			l[j]=t; 
		  }
	  }
  }
  for(i=1;i<=sum;i++)printf("%d %d\n",num[i],l[i]);
return 0;
}
