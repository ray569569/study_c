#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<char> a;
    
    a.push_back('A');
    a.push_back('B');
    vector<char>::iterator b=a.begin();
    for(int i=0;i<2;i++)
    {
        cout<<*(b+i)<<endl;
    }
    b++;
    cout<<*b;
    vector<vector<int >> c(10,vector<int>(10));
    int sum=0;
    for(auto &x:c)
    {
        for(auto &y:x)
        {
            y = sum++;
        }
    }
    for(auto x:c)
    {
        for(auto y:x)
        {
            cout<<y<<" ";
        }
        cout<<endl;
    }
    return 0;
}