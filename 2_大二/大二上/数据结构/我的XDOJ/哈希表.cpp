#include<iostream>
#include <unordered_map>
using namespace std;
unordered_map<int,int>loc;
int main()
{
    int m,p,sum=0,hash_map[101]={0},ans[101],len=0;
    cin>>m>>p;
    while(true)
    {
        int temp;
        cin>>temp;
        if(temp==-1) break;
        if(loc.count(temp)) ans[++len]=loc[temp];
        else
        {        			
	        if(m-1==sum)
	        {
	        	ans[++len]=-1;
	        	break;
			}
			int cnt=0;	    
	        while(hash_map[cnt+temp%p]) cnt++;
	        int answer=cnt+temp%p;
	        hash_map[answer]=1;
	        loc[temp]=answer;
	        sum++;
	        ans[++len]=answer;
    	}
	}
	for(int i=1;i<=len;i++)
	{
		if(ans[i]==-1) cout<<"Table full";
		else cout<<ans[i]<<endl;
	}
    return 0; 
}
