#include<stdio.h>
int n,count=0; //n����ĿҪ������ġ�count������������ 
int a[9]={1,2,3,4,5,6,7,8,9};
int b[10]={0};//�ҵ����� 

void dfs(int num,int space){
	int i,j,m,temp,sum;
	b[space]=num;//��ÿһ���ط�λ�ü�¼��ѡ�� 
	if(space==n-1){//�ߵ�������� 
		sum=0;
		for(j=0,m=0;j<=space;j++){//�������õ���sum 
			if(b[j]==1){//����ֻд�����֣�����+��-��ԭ�����ϡ� 
				temp=a[m];
				for(i=1;b[j+i]==3;i++)	temp=temp*10+a[m+i];
				sum+=temp;
				m=m+i;	
			}
			if(b[j]==2){
				temp=a[m];
				for(i=1;b[j+i]==3;i++)	temp=temp*10+a[m+i];
				sum-=temp;
				m=m+i;
			}
		}
		if(sum==0)	count++;				
		return;
	}
	for(i=1;i<=3;i++)	dfs(i,space+1);    	                                            
}
int main(){
	int k;
	scanf("%d",&n);
	dfs(1,0);
	printf("%d",count);
}/*�ҵ�num��������¼1,2,3��*/

