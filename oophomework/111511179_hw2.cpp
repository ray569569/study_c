#include<iostream>
using namespace std;

void rec(int &a,int &b);

int main()
{
    int number = 0, coupon = 0;
    cin >>number;
    coupon = number;

    rec(number,coupon);

    return 0;
}

void rec(int &a,int &b)
{
    int c =0;
    if(b>=7)
    {
        c = b/7;
        a +=b/7;
        b = b%7;
        b += c;
        return rec(a,b);
    }
    cout<<a<<" "<<b;
}