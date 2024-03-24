#include<stdio.h>
#include<string.h>
void fun(char *s,char *t)
{
    int cnt=0;
	for(int i=0;i<strlen(s);i++)
	{
		if(i%2==0) t[cnt++]=s[i];
	}
}	
 int main()
 {
  char s[1000],*t;
  gets(s);
  fun(s,t);
  printf("%s",s);
return 0;
}
