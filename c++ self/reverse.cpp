#include<iostream>
#include<string>
#include<cstring>
using namespace std;
string reverse(string x);

int main()
{
    string a;
    cin>>a;
    cout<<reverse(a)<<endl;
    return 0;

}

string reverse(string x)
{
    int len= x.size();
    string temp="";
    for(int i=len;i>0;i--)
    {
        temp += x[i-1];
        x.erase(i-1,1);
    }
    return temp;
}