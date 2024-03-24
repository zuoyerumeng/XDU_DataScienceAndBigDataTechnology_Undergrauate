#include <string.h>
#include <stdio.h>
int main()
{
    char s[200],s1[200];
 	int n,max=0;
 	while(1)
 { 
        gets(s);
  		if (strcmp(s,"***end***")==0)
   			 break;
  		n=strlen(s);
  		if(n>max)
  		{
            max=n;strcpy(s1,s);
  		}

}
 printf("%d\n%s\n",max,s1);
 return 0;
}

