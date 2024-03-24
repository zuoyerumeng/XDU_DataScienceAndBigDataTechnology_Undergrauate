#include<stdio.h>
#include<string.h>
int main()
{
	int n,i,j;
	char a[11][20],t[20];
	scanf("%d",&n);
	getchar();
	for(i=1;i<=n;i++) scanf("%s",a[i]);
	for(i=1;i<n;i++)
	{
		for(j=1;j<=i;j++)
		{
			if(strcmp(a[j],a[j+1])>0)
			{
				strcpy(t,a[j]);
				strcpy(a[j],a[j+1]);
				strcpy(a[j+1],t);
			}
		}
	}
   for(i=1;i<n;i++) printf("%s\n\n",a[i]);
 return 0;
}

