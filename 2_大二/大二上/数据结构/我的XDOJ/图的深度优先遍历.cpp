#include<iostream>
using namespace std;
int a[100][100],cnt=0,n,book[100]={0};
void dfs(int s)
{
    cout<<s<<" ";
    book[s]=1;
    cnt++;
    for(int i=1;i<=n;i++)
    {
        if(a[s][i])
        {
            a[s][i]=0;
            a[i][s]=0;
            dfs(i);
        }
    }
    return;
}

int main()
{
    int i,j,ans=0;
    cin>>n;
    for(i=1;i<=n;i++) for(j=1;j<=n;j++) cin>>a[i][j];
    while(cnt<n)
    {
        ans++;
        for(i=1;i<=n;i++)
        {
            if(!book[i])
            {
                dfs(i);
                break;
            }
        }
    }
    cout<<endl;
    cout<<ans;
    return 0;
}
