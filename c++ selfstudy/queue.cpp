#include<iostream>
#include<queue>
using namespace std;
using std::queue;

int main()
{
    queue<int> a;
    for(int i=0;i<5;i++)
    {
        a.push(i);
    }
    
    for(int i=0;i<6;i++)
    {
        cout<<a.front()<<endl;
        a.pop();
    }
    return 0;
}