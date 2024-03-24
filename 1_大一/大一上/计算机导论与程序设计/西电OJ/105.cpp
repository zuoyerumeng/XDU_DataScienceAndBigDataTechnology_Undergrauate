#include<stdio.h>
#include<math.h>
 int main()
 {
  float a,b,c,p,s;
  int i=0;
  while(i==0)
  {
  	scanf("%f%f%f",&a,&b,&c);
  	if(a>0&&b>0&&c>0&&a+b>c&&a+c>b&&b+c>a)
  	{
  	  p=(a+b+c)/2;
      s=sqrt(p*(p-a)*(p-b)*(p-c));
      i=1;
      printf("%f",s);
     }
    else printf("error\n");
  }
return 0;
}
