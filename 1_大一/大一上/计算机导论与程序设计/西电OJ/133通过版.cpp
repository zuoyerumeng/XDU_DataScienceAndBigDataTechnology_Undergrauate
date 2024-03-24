#include <stdio.h>
#include <string.h>

struct ooo	//用结构体做这题方便许多
{
    int coe;
    int exp;
};

int main()
{
    int n,m,t;
    scanf("%d%d%d",&n,&m,&t);
    struct ooo a[200],b[100],temp;
    int i=0,j=0,k=0,l=0;
    for(i=0;i<n;++i)	//我喜欢用++i,听说在某些情况下可以加快运行速度，至于是什么情况我也不知道（手动滑稽*2）
    {
        scanf("%d%d",&a[i].coe,&a[i].exp);
    }
    for(i=0;i<m;++i)
    {
        scanf("%d%d",&b[i].coe,&b[i].exp);
    }
    int tt=1;	//这个tt的作用嘛我也不知道（手动滑稽*3）
    if(t)
        tt=-1;
    for(i=0;i<n;++i)	//遍历a数组和b数组查找指数相等的项，然后。。。
    {
        for(j=0;j<m;++j)	
        {
            if(b[j].coe&&a[i].exp==b[j].exp)	//如果指数相等
            {
                a[i].coe+=tt*b[j].coe;	//使a数组的系数加或减b数组的系数，有了tt以后方便多了
                b[j].coe=0;	//将b数组中这个指数对应的系数置0。它已经没有利用价值了，反而会碍事，宰了
            }
        }
    }
    j=0; 
    for(i=0;i<m;++i)	//遍历b数组
    {
        if(b[i].coe)	//b数组中某一项的系数不为0，说明这一项的指数不等于a数组中的任意一项的指数
        {
            a[n+j].coe=tt*b[i].coe;	//千万别忘了这个tt
            a[n+j].exp=b[i].exp;
            ++j;
        }
    }
    l=j;
 /*   for(i=0;i<n+l;++i)	//这种注释是我找bug留下的产物，今后你的代码也出了bug也可以试试这样做
    {
        printf("coe:%d exp:%d\n",a[i].coe,a[i].exp);
    }*/
    for(i=0;i<n+l-1;++i)	//选择排序法，可能在这里还有更合适的排序法
    {
        k=i;
        for(j=i+1;j<n+l;++j)
        {
            if(a[k].exp>a[j].exp)k=j;	//按指数由小到大排序
        }
        temp=a[i];
        a[i]=a[k];
        a[k]=temp;
    }
/*    for(i=0;i<n+l;++i)
    {
        printf("coe:%d exp:%d\n",a[i].coe,a[i].exp);
    }*/
//    printf("N:%d L:%d\n",n,l);
	int x1=1,x2=0;	//x1判断是否所有项系数都为0，1代表是，0代表否；x2判断是否为第一次输出，0是1否
    for(i=0;i<n+l;++i)	//for循环内部可以简化，但我太懒了
    {					//不过如果你能看懂的话，简化不成问题
        if(a[i].coe)	//如果这一项系数为0，还输出个锤子
        {
//        	printf("...\n");
            if(x2&&a[i].coe>0)printf("+");	//如果这是第一次输出或即将输出的这一项系数小于0，就不要输出加号
            x1=0;x2=1;	//都已经入坑了，说明并不是所有项系数都为0，而且这一项以后所有项都不是第一次输出
            if(a[i].coe==1)	//系数等于1就必须省略系数
            {
                if(a[i].exp==1)	//指数等于1就必须省略^符号和指数
                {
                    printf("x");
                }
                else if(a[i].exp==0)	//指数为0直接输出系数，连“x”都不需要输出
                {
                    printf("%d",a[i].coe);
                }
                else	//输出“x^指数”
                {
                    printf("x^%d",a[i].exp);
                }
            }
            else if(a[i].coe==-1)	//系数等于-1也必须省略系数并在“x”前面加上“-”
            {
                if(a[i].exp==1)	//同上
                {
                    printf("-x");
                }
                else if(a[i].exp==0)	//同上
                {
                    printf("%d",a[i].coe);
                }
                else	//。。。
                {
                    printf("-x^%d",a[i].exp);
                }
            }
            else
            {
                if(a[i].exp==1)
                {
                    printf("%dx",a[i].coe);
                }
                else if(a[i].exp==0)
                {
                    printf("%d",a[i].coe);
                }
                else
                {
                    printf("%dx^%d",a[i].coe,a[i].exp);
                }
            }
        }
    }
    if(x1)	//如果x1等于1，说明所有项均为0，还从未输出过，那么就要输出0
    {
        printf("0");
    }
    return 0;
}


