#include<stdio.h>
 int main()
 {
  char a[8];
  int i;
  for(i=1;i<=7;i++)
  	scanf("%c",&a[i]);
  for(i=1;i<=7;i++)
  {
  	if(a[i]>='A'&&a[i]<='Z')
  	    a[i]=char('A'+('A'-a[i])+25);
  	else if(a[i]>='a'&&a[i]<='z')
  	    a[i]=char('a'+('a'-a[i])+25);
  }
  for(i=1;i<=7;i++)
  printf("%c",a[i]);
return 0;
}
