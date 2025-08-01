#include<iostream>
using namespace std;

bool isPalindrome(string in);

int main()
{
    string input;
    cin>>input;
    if(isPalindrome(input))
    {
        cout<<"Y"<<endl;
    }
    else
    {
        cout<<"N"<<endl;
    }
    return 0;
}

bool isPalindrome(string in)
{
    for(int i=0;i<in.length()/2;i++)
    {
        if(in[i]!=in[in.length()-1-i])
        {
            return false;
        }
    }
    return true;
}