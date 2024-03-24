#include <stdio.h>
#include <string.h>
int main()
{
    char s[201]={},str[201]={},a[4];                                    
    int i,len=0; 
    gets(s);
    while(1)
    {
        scanf("%s",a);
        getchar();  
        if(!strcmp(a,"pwd"))break;  
        gets(str);
        len=strlen(s);
        if(str[0]=='.') 
        {
            i=1;
            while(s[len-i]!='/')    
            {
                s[len-i]='\0';
                ++i;
            }
            s[len-i]='\0';  
            if(!strlen(s))s[0]='/'; 
        }
        else if(str[0]=='/')
        {
            strcpy(s,str);  
        }
        else
        {
            if(len>1)s[len]='/';    
            strcat(s,str);  
        }
        printf("%s\nLEN:%d\n",s,strlen(s));
    }
    printf("%s",s);
    return 0;
}

