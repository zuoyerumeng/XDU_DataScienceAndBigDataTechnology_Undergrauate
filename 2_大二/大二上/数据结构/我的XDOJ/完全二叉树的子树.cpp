#include<iostream>
#include<malloc.h>
using namespace std; 
int q[1000000000]; 
int main()
{
    int m,n,i,*ans,cnt=0;
    ans=(int*)malloc(sizeof(int));
    while(true)
    {
        cin>>m>>n;
        if (!m && !n) break;
        int head=1,tail=0;
        ans[++cnt]=0;
        q[tail++]=m;
        while (head<=tail)
        {
            if(2*q[head]+1<=n) 
            {
                ans[cnt]+=1;
                q[++tail]=2*q[head]+1;
            }
            if(2*q[head]+2<=n) 
            {
                ans[cnt]+=1;
                q[++tail]=2*q[head]+2;
            }
            head++;
        }
    }
    for(i=1;i<=cnt;i++) cout<<ans[i];
    return 0;
}
