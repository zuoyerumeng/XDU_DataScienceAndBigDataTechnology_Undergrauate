#include <iostream>
#define MAX 100000

using namespace std;

int main()
{
	int i=0,j=0,l=0;
	int a[50][50]={0};//�ڽӾ���
	int d[50]={0};//����ʼ��������������·������ 
	int m=0,n=0,k=0;
	int u=0,v=0,w=0;
	int min=0,temp=0;
	int visit[50]={0};//��ǰ��ļ��� 
	
	cin>>m>>n>>k;
	k=k-1;//�±���㿪ʼ������������궼-1 
	visit[k]=1;//����ʼ����뵱ǰ�㼯���� 
	for(i=0;i<n;i++)//��ʼ���ڽӾ��� 
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=MAX;
		}
	}
	
	for(i=0;i<m;i++)
	{
		cin>>u>>v>>w;
		a[u-1][v-1]=w;
	}
	for(i=0;i<n;i++)
	{
		d[i]=a[k][i];//��ʼ��
	}
	
	//ʹ�õϽ�˹�����㷨�������ʼ�㵽ÿһ�������̾���
	//���������ֵ�������ֵΪMAX��˵����ֹһ����ͨ��ͼ�����-1 
	for(i=0;i<n;i++)
	{
		min=MAX,temp=-1;
		for(j=0;j<n;j++)//�ӵ�ǰ��ʼ�㵽�����������ѡһ��� 
		{
			if(!visit[j]&&min>d[j])
			{
				temp=j;
				min=d[j];
			}
		}
		if(temp==-1)//�޷�ʹ���е��յ��ź�
		{
			break;
		}
		visit[temp]=1;//����һ���� 
		for(j=0;j<n;j++)//������֮����ʼ�㵽��������̾��� 
		{
			if(!visit[j]&&min+a[temp][j]<d[j])//�¼����󣬸�����̱� 
			{
				d[j]=min+a[temp][j];
			}
		}
	}
	
	for(i=0,min=-1;i<n;i++)//ѡ��ʱ�����ģ������ΪMAX���޷�ʹ���е㶼�յ��ź�
	{
		if(min<d[i]&&i!=k)
		{
			min=d[i];
		}
	}
	if(min==MAX)
	{
		cout<<"-1";
	}
	else
	{
		cout<<min;
	}
	return 0;
}
