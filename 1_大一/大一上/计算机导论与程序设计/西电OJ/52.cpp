#include<stdio.h>
 int main()
{
 char c,d;
 scanf("%c",&c);
 if(c>='A'&&c<='Z')
 {
   d=char(c+32);
  printf("%c",d);
}
 else if(c>='a'&&c<='z')
 {
   d=char(c-32);
   printf("%c",d);
}
 else 
 {
 d='a';
 printf("%c",c);
}
return 0;
}
