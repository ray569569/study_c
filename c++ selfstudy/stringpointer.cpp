#include<iostream>
#include<string>
using namespace std;

int main()
{
    string *ptr;
    ptr = new string[10];
    
    for(int i=0;i<10;i++)
    {
        *(ptr+i) = char('a'+i);
    }
    
    for(int i=0;i<10;i++)
    {
        cout<< *(ptr+i)<<endl; 
    }
    return 0;
}
