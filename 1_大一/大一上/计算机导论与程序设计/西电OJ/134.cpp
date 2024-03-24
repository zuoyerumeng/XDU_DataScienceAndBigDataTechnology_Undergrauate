#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
 int main()
 {
  char a[10];
  int i,l;
  gets(a);
  l=strlen(a);
  sort(a,a+l);
  for(i=l-1;i>=0;i--)
    printf("%c ",a[i]);
return 0;
}
