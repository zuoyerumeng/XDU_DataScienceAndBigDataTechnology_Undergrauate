#include<iostream>

using namespace std;

int main()
{
	int i=0,j=0,num=0,m=0;
	int n=0,a[100][100]={0},node=0;
	int indegree[100]={0};//������� 
	int visit[100]={0},t=0;
	cin>>m;
	while(num!=m)
	{
		cin>>n;
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				cin>>a[i][j];
				if(a[i][j]==1)
				{
					indegree[j]++;//ͳ����� 
				}
			}
			visit[i]=1;
		}
		
		while(1)//ʹ����������ÿ��ɾ�����Ϊ��ĵ㣬��ɾ���ߣ�������ָ��ı����-1 
		{
			if(node==n)//����n���㱻ɾ���ʾ�޻�
			{
				cout<<"0";
				break;
			}
			
			for(i=0;i<n;i++)//����һ���Ϊ��ĵ� 
			{
				if(indegree[i]==0&&visit[i])
				{
					break;
				}
			}
			
			if(indegree[i]==0&&i<n)//�����Ϊ��ĵ㣬ɾ��ɾ�� 
			{
				t=i,visit[i]=0;//��ʾ���ѱ�ɾ 
				node++;
				for(i=0;i<n;i++)//ɾ���õ���ָ��ıߣ�������ָ��ĵ���ȼ�1 
				{
					if(a[t][i])
					{
						a[t][i]=0;
						indegree[i]--;
					}
				}
			}
			else
			{
				cout<<"1";
				break;
			}
		}
		
		num++,node=0;
		for(i=0;i<n;i++)//����Ա���һ������ 
		{
			for(j=0;j<n;j++)
			{
				a[i][j]=0;
			}
			indegree[i]=0,visit[i]=0;
		}
	}
	return 0;
}
