#include<stdio.h>//目前还未成功。。。 
#include<malloc.h>
#include<math.h>
bool ans()
{
	int len=0;
	char temp,*stack;
	stack=(char*)malloc(sizeof(char));
	while(1)
	{
		scanf("%c",&temp);
		if(temp=='\n') break;
		if(temp=='('||temp=='['||temp=='{')
			stack[++len]=temp;
		else if(temp==')'||temp==']'||temp=='}')
		{
			if(!len) return false;
			if(fabs(stack[len]-temp)>2) return false;
			len--; 
		}
	}
	if(len) return false;
	return true;
}

int main()
{
	bool answer=ans();
	if(answer) printf("right");
	else printf("wrong");
	return 0;
}
