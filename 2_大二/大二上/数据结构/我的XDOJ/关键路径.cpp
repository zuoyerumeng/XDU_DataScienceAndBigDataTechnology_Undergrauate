#include<iostream>
using namespace std; 
int main()
{
    int dp[100]={0},n,i,j,map[100][100],q[100],len=0,indegrees[100]={0},head=1;
    cin>>n;
    for(i=0;i<n;i++) for(j=0;j<n;j++) cin>>map[i][j];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(map[i][j]) indegrees[j]++;
        }
    }
    for(i=0;i<n;i++) if(!indegrees[i]) q[++len]=i;
    while(head<=len)
    {
       int temp=q[head++];
        for(j=0;j<n;j++)
        {
            if(map[temp][j])
            {
                indegrees[j]--;
                if(!indegrees[j]) q[++len]=j;
            }
        }
    }
    if(len!=n) cout<<"NO";
    else
    {
        for(i=0;i<n-1;i++)
        {   
            for(j=i+1;j<n;j++)
            {
                if(map[i][j]!=0 && dp[i]+map[i][j]>dp[j]) dp[j]=dp[i]+map[i][j];
            }
        }
        cout<<dp[n-1];
    }
    return 0;
}
