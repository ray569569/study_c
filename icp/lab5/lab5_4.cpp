#include<iostream>
using namespace std;

int main()
{
    long long sum=0;
    long long mul = 1;
    for(int i=1;i<=20;i++)
    {
        for(int j=1;j<=i;j++)
        {
            mul*=j;
        }
        sum+=mul;
        cout<<i<<" : "<<sum<<endl;
        mul = 1;
    }
    return 0;
}