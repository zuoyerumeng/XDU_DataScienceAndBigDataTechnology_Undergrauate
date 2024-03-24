#include<stdio.h>
int qwe(int n);
int summ(int n); 
 int main()
 {
  int n;
  scanf("%d",&n);
  if(qwe(n)==1)
    printf("%d",summ(n));
  else
    printf("no");
return 0;
}
 int qwe(int n)
{
	int cir=0,x=n;
	while(x!=0)
	{
		cir=cir*10+x%10;
		x=x/10;
	}
	if(cir==n)
	  return 1;
	else
	  return 0; 
}
 int summ(int n)
{
	int sum=0;
	while(n!=0)
	{
		sum=sum+n%10;
		n=n/10;
	}
	return sum;
}
