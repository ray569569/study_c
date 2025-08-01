#include<iostream>
using namespace std;

int binary(int n);

int main()
{
    int in;
    cin>>in;
    cout<<binary(in);
    return 0;
}


int binary(int n)
{
    if(n==0)
        return 0;
    return n%2+10*binary(n/2);
}