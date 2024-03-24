#include<stdio.h>
 int main()
{
 int a,b,c,d,n1=-1,n2=-1;	
 scanf("%d%d%d",&a,&b,&c);
 d=c%10;
 if(a==6||a==7)
    printf("%d no",d);
 else
    if(b<200)
    {
     printf("%d no",d);
    }
    else if(b>=200&&b<400)
    {
      switch(a)
      {
   	    case 1:n1=1;n2=6;break;
    	case 2:n1=2;n2=7;break;
    	case 3:n1=3;n2=8;break;
    	case 4:n1=4;n2=9;break;
    	case 5:n1=5;n2=0;break;
      }
      if(d==n1||d==n2)
         printf("%d yes",d);
      else
         printf("%d no",d);
    }
    else if(b>=400)
        if(a%2==1)
           if(d%2==1)
              printf("%d yes",d);
            else
               printf("%d no",d);
        else
            if(d%2==0)
              printf("%d yes",d);
            else
               printf("%d no",d);  
return 0;
}
 

