 #include<stdio.h>
 #include<string.h>
 int main()
 {
  char str[100][20];
  int i,j,max,sum=0,len[100];
  do
  {
  	sum++;
  	scanf("%s",str[sum]);
  }
  while(str[sum][strlen(str[sum])-1]!='.');
  for(i=1;i<=sum;i++)
     len[i]=strlen(str[i]);
  len[sum]--;
  max=len[1];
  for(i=2;i<=sum;i++)
  {
  	if(len[i]>max)
  	    max=len[i];
  }
  printf("%d",max);
return 0;
}
