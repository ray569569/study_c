#include<iostream>
using namespace std;

string hex(int &a, int &b)
{
    string out;
    int sum = a+b;
    while(sum>0)
    {
        int rem = sum%16;
        if(rem<10)
        {
            out+=to_string(rem);
        }
        else
        {
            out+=char(rem+55);
        }
        sum = sum/16;
    }
    return out;
}

int main()
{
    for(int i=0;i<5;i++)
    {
        int a,b;
        cin>>a>>b;
        string o = hex(a,b);
        for(int j=0;j<o.size();j++)
        {
            cout<<o[o.size()-j-1];
        }
    }
    return 0;
}