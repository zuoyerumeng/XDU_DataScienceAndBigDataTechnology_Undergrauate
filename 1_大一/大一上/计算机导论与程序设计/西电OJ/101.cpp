#include<stdio.h>
 int main()
 {
 char c[4],d[4];
 for(int i=0;i<=3;i++)
 {
 scanf("%c",&c[i]);
 if(c[i]>='A'&&c[i]<='Z')
 {
   d[i]=char(c[i]+32);
  printf("%c",d[i]);
}
 else if(c[i]>='a'&&c[i]<='z')
 {
   d[i]=char(c[i]-32);
   printf("%c",d[i]);
}
  else if(c[i]>='0'&&c[i]<='9')
   printf("*");
  else
  printf("@");
}
return 0;
}
