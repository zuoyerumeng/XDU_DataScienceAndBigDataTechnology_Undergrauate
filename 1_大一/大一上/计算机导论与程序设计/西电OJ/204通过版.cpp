#include <stdio.h>
#include <string.h>
#define SPACE 0 
#define LETTER -1   
#define WORD 1 
void count(char *str,char *word)
{
    int state=0,ans=0,i;  
    int len=strlen(word);
    for(i=0;str[i];++i) 
    {
        switch(state)
        {
        case(SPACE):    
            if(str[i]==word[0])state=WORD; 
            else if(str[i]==' ')state=SPACE;    
            else state=LETTER; 
            break;
        case(LETTER):   
            if(str[i]==' ')state=SPACE; 
            break;
        default:    
            if(state<len)   
            {
                if(str[i]==' ')state=SPACE; 
                else if(str[i]==word[state])++state;   
                else state=LETTER;  
            }
            else if(state==len) 
            {
                if(str[i]==' ') 
                {
                    ans++; 
                    state=SPACE;   
                }
                else state=LETTER;   
            }
        }
    }
    if(state==len) ans++;
    printf("%s %d",word,ans);
}
int main()
{
    char word[9],str[101];
    gets(str);
    gets(word);
    count(str,word);
    return 0;
}


