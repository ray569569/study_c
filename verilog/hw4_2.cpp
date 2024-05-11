#include<iostream>
using namespace std;

int main()
{
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            cout<<"total["<<i<<"]["<<j<<"]<=total["<<i<<"]["<<j<<"] + diff["<<i<<"]["<<j<<"];"<<endl;
        }
    }

    return 0;
}
