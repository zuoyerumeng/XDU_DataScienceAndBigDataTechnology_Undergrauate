#include<iostream>
using namespace std;
int main()
{
	int n,m,t[200][2],ax[200][2],i,j,sum[2];
	sum[0]=0;
	sum[1]=0;
	cin>>n>>m;
	for(i=1;i<=n;i++)
	{
		cin>>t[i][0]>>t[i][1];
		sum[0]+=t[i][0];
		sum[1]+=t[i][1];
	}
	for(i=1;i<=m;i++) cin>>ax[i][0]>>ax[i][1];
	for(i=1;i<=m;i++) cout<<ax[i][0]+sum[0]<<" "<<ax[i][1]+sum[1]<<"\n";
	return 0;
}
