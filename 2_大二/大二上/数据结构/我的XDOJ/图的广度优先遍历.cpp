#include <stdio.h>
int main()
{
    int n,i,j,graph[100][100],q[100],book[100]={0},l=1,r=1,ans=1;
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++) scanf("%d",&graph[i][j]);
    }
    q[1]=1;
    book[1]=1;
    while(r-l+1)
    {
        int temp=q[l++];
        printf("%d ",temp);
        for(i=1;i<=n;i++)
        {
            if(graph[temp][i])
            {
                graph[temp][i]=0;
                if(!book[i])
                {
                    book[i]=1;
                    q[++r]=i;
                }
            }
        }
        if(r-l+1==0)
        {
	        for(i=1;i<=n;i++)
	        {
	        	if(!book[i])
	        	{
	        		ans++;
	        		q[++r]=i;
	        		book[i]=1;
	        		break;
				}
			}
		}
    }
    printf("\n%d",ans);
    return 0;
}
