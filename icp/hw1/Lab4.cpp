#include<iostream>
using namespace std;

int main()
{
    int i=0;
    int sum=0;
    while(sum<10000)
    {
        i++;
        sum+=i;
    }
    cout<<i<<endl;
    return 0;
}