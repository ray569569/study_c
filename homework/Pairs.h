#include<iostream>
#include<fstream>
using namespace std;

class Pairs
{
private:
    int n1;
    int n2;
public:
    Pairs();
    Pairs(int a);
    Pairs(int a,int b);
    friend Pairs operator+(Pairs a,Pairs b);
    friend Pairs operator-(Pairs a,Pairs b);
    friend Pairs operator*(Pairs a,int b);
    friend istream& operator>>(istream& in,Pairs a);
    friend ostream& operator<<(ostream& out,Pairs a);
};
