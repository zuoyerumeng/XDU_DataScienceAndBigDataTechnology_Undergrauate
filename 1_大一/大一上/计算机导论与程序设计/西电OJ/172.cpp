#include<stdio.h>//拿三进制算法做的，各位大佬帮忙看看错在哪里（手动哭脸*3） 
#include<math.h>
using namespace std;
int main()
{
    int n,y=0;
    int v[100],a[100],x;
    scanf("%d",&n);
    for (int i = 0,j=1; i < 2*n-1;i+=2,j++) v[i] = j;
    for (int j = pow(3.0, (double)(n - 2)); j <pow(3.0, (double)(n-1));j++)
	{
        int t = j;
        for (int i = 2*n-3; i>0;i-=2)
		{
            v[i] = t % 3;
            t/= 3;
        }
        a[0] = v[0];
        x = 0;
        for (int k = 1; k < (n - 1) * 2;k+=2)
		{
            if(v[k]==0)a[x] = a[x] * 10 + v[k + 1];
            else
			{
                x++;
                a[x] = v[k];
                x++;
                a[x] = v[k + 1];
            }
        }
        for (int i = 1;i<=x ;i+=2)
		{
                if(a[i]==1)a[i + 1] += a[i - 1];
                else a[i+ 1] -= a[i - 1];
        }
        if(a[x]==0)y++;
    }
    printf("%d",y);
}

