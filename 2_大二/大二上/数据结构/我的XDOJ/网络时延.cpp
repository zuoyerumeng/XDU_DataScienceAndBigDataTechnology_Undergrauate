#include<iostream>
#define Max 1000
using namespace std;

int main()
{
    int i,m,n,k,dp[21],edge[51][3];
    cin>>m>>n>>k;
    for(i=1;i<=n;i++) dp[i]=Max;
    dp[k]=0;
    for(i=1;i<=m;i++) cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
	for(i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(dp[edge[j][0]]+edge[j][2]<dp[edge[j][1]])
				dp[edge[j][1]]=dp[edge[j][0]]+edge[j][2];	
		}
	}
    int flag=1,ans=0;
    for(i=1;i<=n;i++)
    {
        if(dp[i]==Max)
        {
            flag=0;
            cout<<-1;
            break;
        }
        if(dp[i]>ans) ans=dp[i];
    }
    if(flag) cout<<ans;
    return 0;
}
