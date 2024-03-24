#include<stdio.h>//»¹Î´debugÍê¡£¡£ 
#include <malloc.h>
int main()
{
    int m,n,a[100][100],i,j,sx,sy,ex,ey,next[4][2]={{-1,0},{0,1},{1,0},{0,-1}},ans[10000][3]={0},len_ans=0,len_stack=0,stack[10000][2];
    scanf("%d%d",&m,&n);
    scanf("%d%d",&sx,&sy);
    scanf("%d%d",&ex,&ey);
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
        }
    }
    stack[len_stack][0]=sx,stack[len_stack++][1]=sy;
    while(len_stack)
    {
        int tempx=stack[len_stack-1][0],tempy=stack[len_stack--][1];
		ans[len_ans][0]=tempx,ans[len_ans++][1]=tempy;        
        if(tempx==ex && tempy==ey)
        {
            for(i=0;i<len_ans;i++)
                printf("(%d,%d,%d),",ans[i][0],ans[i][1],ans[i][2]);
            printf("\b");
            break;
        }
        int flag1=0;
        for(i=0;i<4;i++)
        {
            if(1<=tempx+next[i][0] && tempx+next[i][0]<=m && tempy+next[i][1]>=1 && tempy+next[i][1]<=n && !a[tempx+next[i][0]][tempy+next[i][1]])
            {
                flag1=1;
                a[tempx+next[i][0]][tempy+next[i][1]]=1;
                stack[len_stack][0]=tempx+next[i][0];
                stack[len_stack++][1]=tempy+next[i][1];
            }
           
        } 
        if(!flag1) len_ans--;
        while(len_ans)
        {
            int flag2=0;
            for(j=0;j<len_stack;j++)
            {
                if(stack[j]==ans[len_ans-1])
                {
                    flag2=1;
                    break;
                }
            }
            if(!flag2) len_ans--;
            else break;
        }
        if(!len_ans)
        {
            printf("no");
            return 0;
        }
    }
    return 0;
}
