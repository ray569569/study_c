#include<iostream>
using namespace std;

int main()
{
    char in;
    int shift;
    char out;
    cout<<"please input the shift amount: ";
    cin>>shift;
    cout<<"please input a char: ";
    cin>>in;

    
    
    if(in>='a'&&in<='z')
    {
        if(('a'-in)>shift)
            shift+=26;

        if(('z'-in)<shift)
            shift-=26;
    }

    if(in>='A'&&in<='Z')
    {
        if(('A'-in)>shift)
            shift+=26;

        if(('Z'-in)<shift)
            shift-=26;
    }
    out = in+shift;
    cout<<"the char being replaced is: "<<out;
    return 0;

}