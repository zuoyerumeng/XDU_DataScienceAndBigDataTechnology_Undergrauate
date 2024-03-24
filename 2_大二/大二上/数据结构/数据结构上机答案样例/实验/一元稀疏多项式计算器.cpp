#include<stdio.h>
#include<string.h>
#include<math.h>
#include<list>
int main()
{
	int n,i,value[101][2]={0},cnt=0,book[101],len_book=0;
    char address[101][2][6],head[6],temp[6];
    list<int> address;
    list<int> value;
    scanf("%s%d",head,&n);
    for(i=1;i<=n;i++)
    {
        scanf("%s%d%s",address[i][0],&value[i][0],address[i][1]);
    }
    address.push_back(head);
    while(cnt<n)
    {
        for(i=1;i<=n;i++)
        {
        	//printf("%s %s %d\n",head,address[i][0],strcmp(head,address[i][0]));
            if(!value[i][1] && !strcmp(head,address[i][0]))
            {
                value[i][1]=1;
                address.push_back(address[i][1]);
                val.push_back(value[i][0]);
                // int flag=1;
                // for(int j=1;j<=len_book;j++)
                // {
                //     if(!(book[j]-abs(value[i][0])))
                //     {
                //         flag=0;
                //         break;
                //     }
                // }
                // if(flag)
                // {
                    
                //     book[++len_book]=abs(value[i][0]);
                // }
                strcpy(head,address[i][1]);
                break;
            }
        }
        cnt++;
    }
    address.unique();
    value.unique();
    int head_address=address.begin();
    int head_value=value.begin();
    int flag=0;
    while(head_address<=address.end() && head_value<=value.end())
    {
        if(flag) printf("%s\n",head_address);
        flag=1;
        printf("%s %d ",head_address,head_value);
        head_address++;
        head_value++;
    }
    return 0;
 } 