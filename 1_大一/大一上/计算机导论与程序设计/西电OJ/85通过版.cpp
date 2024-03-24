#include<stdio.h>
#include<string.h>
void transf(char *p)
{ int i;
    for(i=0;*(p+i)!='\0';i++)
	{
	if( *(p+i) >= 'a' && *(p+i) <= 'z' )
		*(p+i) =*(p+i)-32 ;
	}
}
int main()
{  double result;
  char s1[100],s2[100],s3;
	int i,j,number=0,max=0;
 	gets(s1);
 	gets(s2);
 	  transf(s1);
 	  transf(s2);
 	int l1=strlen(s1),l2=strlen(s2);
 	int t1,t2;
 			for(i=0;i<l1;i++)
 				for(j=0;j<l2;j++)//主要思想还是将重复的地方找到
			 	{if(s2[j]==s1[i])
				 t1=i;t2=j;
				for(;s2[t2]==s1[t1]&&s2[t2]!='\0'&&s1[t1]!='\0';t1++,t2++)
				{	number++;
				}
				 if(number>=max)
					{ max=number;
					number=0;
					}
					else number=0;
			   }
		result=(2*(double)max)/((double)(l1)+(double)(l2));
		printf("%.3lf",result);
}

