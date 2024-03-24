#include<stdio.h>
 int fib(int n);
 int main()
 {
  int n;
  scanf("%d",&n);
  printf("%d",fib(n));
return 0;
}
 int fib(int n)
 {
 	int a[40];
 	a[0]=7;
 	a[1]=11;
 	for(int i=2;i<=n;i++)
 	a[i]=a[i-1]+a[i-2];
 	return(a[n]);
 }
