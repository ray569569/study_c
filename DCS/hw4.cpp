#include<iostream>
using namespace std;

int main()
{
    int count=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            cout<<"assign temp["<<j<<"]["<<i<<"] = in_data-image[count_x-"<<j<<"][count_y-"<<i<<"];"<<endl;
        }
    }
    return 0;
}