#include<iostream>
#include<algorithm>
using namespace std;
int main()
{
	int i,j,n,m,edge[101][3],book[31]={0},sum=0,cur_edge=1;
	cin>>n>>m;
	for(i=1;i<=m;i++) cin>>edge[i][0]>>edge[i][1]>>edge[i][2];
	for(i=1;i<=m-1;i++)
	{
		for(j=m+1-i;j>=1;j--)
		{
			if(edge[j][2]<edge[j-1][2])
			{
				for(int k=0;k<3;k++) swap(edge[j][k],edge[j-1][k]);
			}
		}
	}
	while(sum<n)
	{
		while(book[edge[cur_edge][0]] && book[edge[cur_edge][1]]) cur_edge++;
		sum+=2-book[edge[cur_edge][0]]-book[edge[cur_edge][1]];
		book[edge[cur_edge][0]]=1;
		book[edge[cur_edge][1]]=1;
		cout<<min(edge[cur_edge][0],edge[cur_edge][1])<<" "<<max(edge[cur_edge][0],edge[cur_edge][1])<<" "<<edge[cur_edge][2]<<endl;
		cur_edge++;
	}
	return 0;
}
