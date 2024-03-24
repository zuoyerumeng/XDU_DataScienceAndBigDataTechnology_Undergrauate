#include <stdio.h>
#include <malloc.h>
#include <string.h>
int  main()
{
    int i,ans=0,l;
    char *s;
    s=(char*)malloc(sizeof(char));
    gets(s);
    l=strlen(s)-1;
    for(i=0;i<l;i++)
    {
        if(i<l/2)
        {
            if(s[i]!='@'&&s[2*i+1]=='@'&&s[2*i+2]=='@')
            {
            	printf("%c ",s[i]);
            	ans++;
			}
        }
        else
        {
            if(s[i]!='@')
            {
            	printf("%c ",s[i]);
            	ans++;
			}
        }
    }
    printf("\n%d",ans);
    return 0;
}
