#include<stdio.h>
 int main()
 {
  int m,b,i,a[4],min,max;
  scanf("%d%d",&m,&b);
  a[0]=(m+b)*(m+b);
  a[1]=(m-b)*(m-b);
  a[2]=m*m+b*b;
  a[3]=m*m-b*b;
  min=a[0];
  max=a[0];
  for(i=1;i<=3;i++)
  {
  if(a[i]<min)
    min=a[i];
}
   for(i=1;i<=3;i++)
  {
  if(a[i]>max)
    max=a[i];
}
  printf("%d %d",max,min);
return 0;
}
