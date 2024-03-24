#include<stdio.h>
#include<algorithm>
using namespace std;
int main()
{
	int j,i,sum;
  	char a[1000];
   	sum = 0;
  	gets(a);
  	for (j = 0; a[j] != '\0'; j++) 
	    sum++;
  	sort(a,a+sum);
  	for(i=0;i<sum;i++)
  	    printf("%c",a[i]);
	return 0;
}


