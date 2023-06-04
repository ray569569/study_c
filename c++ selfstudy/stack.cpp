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

    while(!sta.empty())
    {
        cout<<sta.top();
        sta.pop();
    }
    return 0;
}
