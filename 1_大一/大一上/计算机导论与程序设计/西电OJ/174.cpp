#include <stdio.h>
int dp[205][20005]={0};
int main(){
	int v_w[205]={0};
	int n,i,j,sum=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{    
		scanf("%d",&v_w[i]);
		sum+=v_w[i];
	}
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=(sum/2);j++)
		{
			if(v_w[i]>j)dp[i][j]=dp[i-1][j];
			else dp[i][j]=(dp[i-1][j]>dp[i-1][j-v_w[i]]+v_w[i])?dp[i-1][j]:dp[i-1][j-v_w[i]]+v_w[i];
		}
	}
	if((sum-2*dp[n][sum/2])>0)printf("%d",(sum-2*dp[n][sum/2]));
	else printf("%d",-(sum-2*dp[n][sum/2]));
	return 0;
}
 

