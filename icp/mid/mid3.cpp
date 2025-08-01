#include<iostream>
using namespace std;

void bin_to_hex(int n,int len)
{
    if(len>4)
    {
        int temp = n/10000;
        bin_to_hex(temp,len-=4);
    }
    n%=10000;
    if(n == 0)
        cout<<"0";
    else if(n == 1)
        cout<<"1";
    else if(n == 10)
        cout<<"2";
    else if(n == 11)
        cout<<"3";
    else if(n == 100)
        cout<<"4";
    else if(n == 101)
        cout<<"5";
    else if(n == 110)
        cout<<"6";
    else if(n == 111)
        cout<<"7";
    else if(n == 1000)
        cout<<"8";
    else if(n == 1001)
        cout<<"9";
    else if(n == 1010)
        cout<<"A";
    else if(n == 1011)
        cout<<"B";
    else if(n == 1100)
        cout<<"C";
    else if(n == 1101)
        cout<<"D";
    else if(n == 1110)
        cout<<"E";
    else if(n == 1111)
        cout<<"F";
    else
        cout<<"error";

}

int main()
{
    int a,b,bin;
    cout<<"please input number 1: ";
    cin>>a;
    cout<<"please input number 2: ";
    cin>>b;
    
    int temp,exp;
    exp = 1;
    temp = a+b;
    bin = a+b;
    int len=0;
    while(temp!=0)
    {
        
        if(temp%10 == 2)
        {
            bin+=8*exp;
            temp +=8;
        }
        else if(temp%10 == 3)
        {
            bin+=8*exp;
            temp +=8;
        }
        exp*=10;
        temp/=10;
        len+=1;
    }
    
    cout<<"bin: "<<bin<<endl;
    cout<<"hex: ";
    bin_to_hex(bin,len);
    return 0;
    

}