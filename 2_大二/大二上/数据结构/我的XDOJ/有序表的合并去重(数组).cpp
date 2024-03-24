#include<iostream>
#include<list>
#include<algorithm> 
using namespace std;
int main()
{
	int a,b,i,temp;
    list<int> ans;
    cin>>a>>b;
    for(i=1;i<=a;i++)
    {
        cin>>temp;
        ans.push_back(temp);
    }
    for(i=a+1;i<=a+b;i++) 
    {
        cin>>temp;
        ans.push_back(temp);
    }
    ans.sort();
	ans.unique();
    list<int>::iterator head=ans.begin();
    for(i=1;i<=ans.size();i++,head++) printf("%d ",*head);
    return 0;
 } 

