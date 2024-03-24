#include<iostream>
#include<string>
#include<math.h>
#include<list>
using namespace std; 
int main()
{
	int n,i,value[101][2]={0},cnt=0,book[101],len_book=0;
    string address[101][2],head;
    list<string> ans_address;
    list<int> ans_value;
    cin>>head>>n;
    for(i=1;i<=n;i++)
    {
        cin>>address[i][0]>>value[i][0]>>address[i][1];
    }
    while(cnt<n)
    {
        for(i=1;i<=n;i++)
        {
            if(!value[i][1] && head==address[i][0])
            {
                value[i][1]=1;
                int flag=1;
                for(int j=1;j<=len_book;j++)
                {
                    if(!(book[j]-abs(value[i][0])))
                    {
                        flag=0;
                        break;
                    }
                }
                if(flag)
                {
                    ans_address.push_back(address[i][0]);
                    ans_value.push_back(value[i][0]);
                    book[++len_book]=abs(value[i][0]);
                }
                head=address[i][1];
                break;
            }
        }
        cnt++;
    }
    ans_address.push_back("-1");
	list<string>::iterator head_address=ans_address.begin();
    list<int>::iterator head_value=ans_value.begin();
    int flag=0;
    cout<<ans_value.size()<<'\n'; 
    while(1)
    {
        cout<<*head_address<<' '<<*head_value<<' ';
        head_address++;
        cout<<*head_address<<'\n';
        head_value++;
        if(*head_address=="-1") break;
    }
    return 0;
 } 
