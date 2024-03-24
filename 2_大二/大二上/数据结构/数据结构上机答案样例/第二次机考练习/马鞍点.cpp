#include<stdio.h>
#include<iostream>
using namespace std;
void get_next(char str[],int next[],int n,int m)
{
	int i=1,j=0;
	next[1]=0;
	while(i<n)
	{
		if(j==0||str[i]==str[j])
		{
			i++;j++;
			next[i]=j;
		}
		else
		{
			j=next[j];
		}
	}	
}
int main()
{
	int n;
	cin>>n;
	char str[n+1];
	str[0]=n;
	int i,j;
	for(i=1;i<=n;i++)
	{
		cin>>str[i];
	}
	int next[n+1];
	get_next(str,next,n+1,n+1);
	for(i=1;i<=n;i++)
		cout<<next[i]-1<<' ';
	return 0;
}

