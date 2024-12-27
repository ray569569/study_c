#include<iostream>
using namespace std;

int main()
{
    int num;
    int sum;
    for(int i=0;i<5;i++)
    {
        cout<<"please input a nunnegative number: ";
        cin>>num;
        sum = 1;
        for(int j=1;j<=num;j++)
        {
            sum*=j;
        }
        cout<<sum<<endl;
    }
    return 0;
}