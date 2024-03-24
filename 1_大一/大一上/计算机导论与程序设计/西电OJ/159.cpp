#include<stdio.h>
int function(int n);
 int main()
 {
  int m,n;
  float a,b,c;
  scanf("%d%d",&m,&n);
  a=(float)function(m);
  b=(float)function(n);
  c=(float)function(m-n);
  printf("%.2f",a/b/c);
return 0;
}
int function(int n)
{
	int t=1;
	for(int i=2;i<=n;i++)
		t=t*i;
	return(t);
}
