#include<iostream>
#include<stack>
using namespace std;

int main()
{
    stack<int> sta;

    int temp;
    for(int i=0;i<5;i++)
    {
        cin>>temp;
        sta.push(temp);
    }
    stack<int> t;
    t=sta;
    while(!t.empty())
    {
        cout<<t.top();
        t.pop();
    }
    return 0;
}
