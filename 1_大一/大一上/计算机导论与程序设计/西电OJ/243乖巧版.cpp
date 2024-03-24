#include<stdio.h>
 int main()
{
  struct 
 { 
  char name[20];
  int a[7],sum;
 }stu[101],t;
  int n,i,j;
  scanf("%d",&n);
  for(i=1;i<=n;i++)
  {
    stu[i].sum=0;
	scanf("%s",stu[i].name);
    for(j=1;j<=6;j++)
  {
    scanf("%d",&stu[i].a[j]);
    stu[i].sum+=stu[i].a[j];
  }
 }
  for(i=1;i<=n-1;i++)
  {
   for(j=1;j<=n-i;j++)
   {
    if(stu[j].sum<stu[j+1].sum||(stu[j].sum==stu[j+1].sum&&stu[j].a[6]<stu[j+1].a[6]))
    {
      t=stu[j];
      stu[j]=stu[j+1];
      stu[j+1]=t;
    }
   }
  }
 for(i=1;i<=n;i++)printf("%s %d %d\n",stu[i].name,stu[i].sum,stu[i].a[6]);
return 0;
}
