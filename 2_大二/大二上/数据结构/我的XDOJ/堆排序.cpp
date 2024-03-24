#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
int main()
{
    int i,m,n[100];
    cin>>m;
    for(i=1;i<=m;i++) cin>>n[i];
    make_heap(n+1,n+m+1,greater<int>());
    for(i=1;i<=m;i++) cout<<n[i]<<" ";
    return 0;
}
