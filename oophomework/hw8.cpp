#include<iostream>
#include"Pairs.h"
using namespace std;

istream& operator>>(istream& in,Pairs a)
{
    in>>a.n1>>a.n2;
    return in;
}
ostream& operator<<(ostream& out,Pairs a)
{
    out<<a.n1<<" "<<a.n2<<endl;
    return out;
}

Pairs operator+(Pairs a,Pairs b)
{
    Pairs c;
    c.n1 = a.n1+b.n1;
    c.n2 = a.n2+b.n2;
    return c;
}
Pairs operator-(Pairs a,Pairs b)
{
    Pairs c;
    c.n1 = a.n1-b.n1;
    c.n2 = a.n2-b.n2;
    return c;
}
Pairs operator*(Pairs a,int b)
{
    Pairs c;
    c.n1 = a.n1*b;
    c.n2 = a.n2*b;
    return c;
}
Pairs::Pairs()
{
    n1=0;
    n2=0;
}
Pairs::Pairs(int a)
{
    n1 = a;
    n2 = 0;
}
Pairs::Pairs(int a,int b)
{
    n1=a;
    n2=b;
}

int main()
{
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    Pairs o1(a,b);
    Pairs o2(c);
    cout<<o1+o2<<o1-o2<<o1*d<<endl;
    return 0;
}
