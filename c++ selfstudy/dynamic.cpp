#include<iostream>
using namespace std;

int main()
{
    int sum=0;
    int** array;
    array = new int*[5];
    
    for(int i=0;i<5;i++)
    {
        array[i] = new int[3];
        for(int j=0;j<3;j++)
        {
            array[i][j] = sum++;
        }
    }
    for(int i=0;i<5;i++)
    {
        
        for(int j=0;j<3;j++)
        {
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }
}