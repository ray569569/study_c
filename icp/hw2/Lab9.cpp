#include<iostream>
using namespace std;

int main()
{
    for(char i='A';i<='Z';i++)
    {
        cout<<i<<" "<<int(i)<<" ";
        if((i-'A')%2 == 1)
        {
            cout<<endl;
        }
    }
    return 0;
}