#include<iostream>
using namespace std;

int main()
{
    int input;
    cout<<"please enter a binary number: ";
    cin>>input;
    int sum = 0;
    int i=1;
    while(input!=0)
    {
        sum+= (input%10) * i;
        input/=10;
        i*=2;
    }
    cout<<sum;
    return 0;
}