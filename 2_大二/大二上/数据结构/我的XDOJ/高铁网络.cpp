#include <iostream>
#include <unordered_map>//MFSet(并查集）实现 
//#include <algorithm>
using namespace std;

unordered_map<int,int>f;
unordered_map<int,int>book; 

int find(int x)
{
    if(!f.count(x)) return f[x]=x;
    if(f[x]!=x) f[x]=find(f[x]);
    return f[x];
}

void uni(int x,int y)//union
{
    f[find(x)]=find(y);
}

int main()
{
    int m,n,i,t1,t2,cnt=0,unique[31],len=0;
    cin>>n>>m;
    for(i=1;i<=m;i++)
    {
        cin>>t1>>t2;
        uni(t1,t2);
    }
    for(i=1;i<=n;i++)
    {
        if(!book.count(find(i)))
        {
            book[find(i)]=1;
            unique[++len]=find(i); 
            cnt++;
        }
        //else book[find(i)]++; 
    }
    cout<<cnt-1<<endl;
//    for(i=1;i<=len;i++) unique[i]=book[unique[i]];
//    sort(unique+1,unique+1+len);
//    for(i=1;i<=len;i++) cout<<unique[i]<<" ";
    return 0;
}
