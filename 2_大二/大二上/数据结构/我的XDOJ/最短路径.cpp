#include <iostream>

using namespace std;

int main()
{
	int i=0,j=0,n=0,k=0,temp=0;
	int a[100][100]={0};
	int start=0,end=0;//�������� 
	int path[100][100]={0};//���Լ�¼·�� 
	int out[100]={0},t=0;

	cin>>n;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cin>>a[i][j];
			path[i][j]=j;
		}
	}
	
	for(k=0;k<n;k++)//���������㷨��ÿ�ζ��һ���������·�� 
	{
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
			{
                if(a[i][k]+a[k][j]<a[i][j])
				{
                    a[i][j]=a[i][k]+a[k][j];
                    path[i][j]=path[i][k];
                }
            }
        }
    }
    
    while(1)
    {
    	cin>>start>>end;
    	if(start==-1&&end==-1)
    	{
    		break;
		}
		else
		{
			if(a[start][end]==10000)
			{
				cout<<"NO"<<endl;
			}
			else
			{
				t=0;
				cout<<a[start][end]<<endl;
				cout<<start<<" ";
				while(start!=end)
				{
					cout<<path[start][end]<<" ";
					start=path[start][end];
				}
				cout<<endl;
			}
		}
	}
	return 0;
 }
