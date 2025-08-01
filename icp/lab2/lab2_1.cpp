#include<iostream>
#include<ctime>
using namespace std;

int main()
{
    srand(time(0));
    int n = rand() % 101 ;
    int a;
    cin>>a;
    while(a!=n)
    {
        if(a>n)
        {
            cout<<"too big, please input a number between 0 and "<<a<<endl;
        }
        else
        {
            cout<<"too small, please input a number between "<<a<<" and 100"<<endl;
        }
        cin>>a;
    }
    return 0;
}