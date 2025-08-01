#include<iostream>
using namespace std;

string reverseNumber(string in);

int main()
{
    string input;
    int i=0;
    while(i<5)
    {
        i++;
        cout<<"please enter a number: ";
        cin>>input;
        cout<<"The reverse of the number is: "<<reverseNumber(input)<<endl;
    }
    return 0;
}

string reverseNumber(string in)
{
    string out="";
    for(int i=in.length()-1;i>=0;i--)
    {
        out+=in[i];
    }
    while(out[0]=='0')
    {
        out.erase(0,1);
    }
    
    return out;
}