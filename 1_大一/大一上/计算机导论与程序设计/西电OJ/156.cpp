#include<stdio.h>
 int main()
 {
 	int s=0;
 	for(int i=100;i<=500;i++)
 	{
 		if((i%7==0||i%11==0)&&i%77!=0)
 		s+=1;
	 }
	 printf("%d",s);
return 0;
}
