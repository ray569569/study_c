#include<iostream>
using namespace std;

int main()
{
    int a,b;
    cout<<"please enter two positive numbers: ";
    cin>>a>>b;
    while(b<=a)
    {
        cout<<"please enter a number greater than the first number: ";
        cin>>b;
    }
    int sum = 0;
    for(int i=a;i<=b;i++)
    {
        if(i%2==0)
        {
            sum+=i;
        }
    }
    cout<<"The sum of all even numbers in this range is: "<<sum<<endl;
    return 0;
}