#include<iostream>
using namespace std;

int main()
{
    float TWD,USD;
    cout<<"Please input how much TWD you have:";
    cin>>TWD;
    USD = TWD / 30.5;
    cout<<"You have "<<int(USD)<<" USD"<<endl;
    cout<<"You can spend "<<int(USD*0.5)<<" USD on clothes."<<endl;
    cout<<"You can spend "<<int(USD*0.3)<<" USD on food."<<endl;
    cout<<"You can spend "<<int(USD*0.2)<<" USD on sourvenir."<<endl;
    return 0;
}