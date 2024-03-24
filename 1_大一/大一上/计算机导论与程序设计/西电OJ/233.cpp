#include<stdio.h>
#include<string.h>
 int main()
 {
  char a[1005];
  int len,n,i;
  gets(a);
  len=strlen(a);
  scanf("%d",&n);
  if(len<n)
    printf("error");
  else
  {
  	for(i=n-1;i<len;i++)
      printf("%c",a[i]);
  }
return 0;
}
