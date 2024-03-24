#include<stdio.h>
int main()
{
	int j, sum;
  	char a[100];
   	sum = 0;
  	gets(a);
  	for (j = 0; a[j] != '\0'; j++) sum += a[j];
  	printf("%d", sum%256);
	return 0;
}


