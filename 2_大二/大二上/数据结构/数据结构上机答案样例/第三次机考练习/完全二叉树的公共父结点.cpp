#include<stdio.h>
int main()
{
	int x,y;
	while(scanf("%d %d",&x,&y)!=EOF&&x+y!=0)//因为有多组数据所以当测试文件结束时或输入为00时结束运算
	//这个x+y！=0（即输入为00）是在多次unaccept后发现的，起初我不知道题目中给的测试用例为什么会多出来两个0
	//多次错误后我猜到那可能是结束的条件，我加上之后就ac了。
	{
	while(x!=y)
	{
     if(x>y)
		 x=x/2;//x得到其父亲节点
	 if(x<y)
		 y=y/2;
	}
	printf("%d\n",x);
	}
	return 0;
}

