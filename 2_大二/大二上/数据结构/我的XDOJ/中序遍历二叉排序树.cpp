#include <algorithm>
#include <stdio.h>
using namespace std;
int main()
{
    int i,m,n[100];
    scanf("%d",&m);
    for(i=1;i<=m;i++)
    {
        scanf("%d",&n[i]);
    }
    sort_heap(n+1,n+m+1);
    for(i=1;i<=m;i++) printf("%d ",n[i]);
    return 0;
}
