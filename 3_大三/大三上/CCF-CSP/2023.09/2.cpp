#include<iostream>
#include<math.h>
#include<iomanip>
using namespace std;
double k[100001],theta[100001],ax[100001][4];
int main()
{
	int n,m,type,i,j;
	double value;
	cin>>n>>m;
	k[0]=1;
	theta[0]=0;
	for(i=1;i<=n;i++)
	{
		cin>>type>>value;
		k[i]=k[i-1];
		theta[i]=theta[i-1];
		if(type==1) k[i]*=value;
		else theta[i]+=value;
	}
	for(i=1;i<=m;i++) cin>>ax[i][0]>>ax[i][1]>>ax[i][2]>>ax[i][3];
	for(i=1;i<=m;i++)
	{
		double k_sub=k[int(ax[i][1])]/k[int(ax[i][0])-1];
		double theta_sub=theta[int(ax[i][1])]-theta[int(ax[i][0])-1];
		cout<<fixed<<setprecision(3)<<(double)k_sub*(ax[i][2]*cos(theta_sub)-ax[i][3]*sin(theta_sub))<<" "<<(double)k_sub*(ax[i][2]*sin(theta_sub)+ax[i][3]*cos(theta_sub))<<"\n";
	}		
	return 0;
}
