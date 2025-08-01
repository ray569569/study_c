#include<iostream>
using namespace std;

int main()
{
    int shares = 750;
    cout<<"total amount paid for the stock: "<<shares*35<<endl;
    cout<<"total amount of received: "<<shares*31.15<<endl;
    cout<<"total amount of money she lost: "<<shares*35-shares*31.15<<endl;
    return 0;
}