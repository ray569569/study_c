#include<iostream>
using namespace std;

void calculate(int a, int b,char oper);

int main()
{
    int A,B;
    char op;
    cout<<"Please input A:"<<endl;
    cin>>A;
    cout<<"Please input B:"<<endl;
    cin>>B;
    cout<<"Please input operator(+,-,*,/):"<<endl;
    cin>>op;
    calculate(A,B,op);
    return 0;
}

void calculate(int a, int b,char oper)
{
    switch(oper)
    {
        case '+':
            cout<<a<<"+"<<b<<"="<<a+b<<endl;
            break;
        case '-':
            cout<<a<<"-"<<b<<"="<<a-b<<endl;
            break;
        case '*':
            cout<<a<<"*"<<b<<"="<<a*b<<endl;
            break;
        case '/':
            if(b==0)
            {
                cout<<"Error: division by zero"<<endl;
            }
            else
            {
                cout<<a<<"/"<<b<<"="<<a/b<<endl;
            }
            break;
        default:
            cout<<"Error: invalid operator"<<endl;
    }
}