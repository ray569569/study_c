#include<iostream>
using namespace std;

void prt(int* a)
{
    for(int i=0;i<5;i++)
    {
        cout<<a[i]<<endl;
    }
}
int main()
{
    int arr[5]={1,2,3,4,5};
    prt(arr);
    return 0;
}