#include<iostream>
#include<fstream>
using namespace std;

class test
{
private:
    int cent;
    int doller;
    int sum;
public:
    void friend operator +(test &X);    
    bool friend operator ==(const test a,const test b);
    friend ostream& operator <<(ostream& out ,test a);
    void setvalue(int a,int b);
    void printvalue();
};
ostream& operator <<(ostream& out,test a)
{
    out<<a.sum;
    return out;
}

void test::setvalue(int a,int b)
{
    doller =a;
    cent =b;
}
void test::printvalue()
{
    cout<<cent<<endl<<doller<<endl<<sum<<endl;
}
void operator +(test &X)
{
    X.sum = X.cent+X.doller*100;
}

bool operator ==(const test a,const test b)
{
    if(a.sum == b.sum)
    {
        return 1;
    }
    else 
    return 0;
}
int main()
{
    test a,b;
    a.setvalue(10,5);
    +(a);
    b.setvalue(0,1005);
    +(b);
    //a.printvalue();
    bool k = a==b;
    cout<<b<<endl<<a<<endl<<k<<endl;

    return 0;
}