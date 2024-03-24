#include<stdio.h>
#include<iostream>
#include<algorithm>
#define N 10000000
using namespace std;
int main()
{
    int i,n,a[30],ans=0;
    cin>>n;
    for(i=1;i<=n;i++) cin>>a[i];
    for(i=1;i<n;i++)
    {
        sort(a+1,a+n+1);
        ans+=a[1]+a[2];
        a[2]+=a[1];
        a[1]=N;
    }
    cout>>ans;
}