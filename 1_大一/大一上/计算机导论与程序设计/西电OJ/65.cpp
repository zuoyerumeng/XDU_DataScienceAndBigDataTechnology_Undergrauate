#include<stdio.h>
 int function(int n);
 int main()
 {
  int n;
  scanf("%d",&n);
  printf("%d",function(n));
return 0;
}
 int function(int n)
 {
  int a[11],i=0,p=0,sum=0;
  while(n!=0)
 {
    i++;
	a[i]=n%10;
    n=n/10;
    p++;
    sum+=a[i];
 }
  if(sum<=9)
    return(sum);
  else
    return(function(sum));
}
