#include<stdio.h>
int n,count=0; //n是题目要求输入的、count是用来计数的 
int a[9]={1,2,3,4,5,6,7,8,9};
int b[10]={0};//找到命令 

void dfs(int num,int space){
	int i,j,m,temp,sum;
	b[space]=num;//对每一个地方位置记录下选择 
	if(space==n-1){//走到了最深处了 
		sum=0;
		for(j=0,m=0;j<=space;j++){//计算最后得到的sum 
			if(b[j]==1){//这里只写了两种，就是+和-，原因如上。 
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
}/*我的num是用来记录1,2,3的*/

