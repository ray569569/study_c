#include<iostream>
#include<vector>
using namespace std;

int main()
{
    string line;
    getline(cin,line);
    for(int i=0;i<line.size();i++)
    {
        cout<<char(line[i]+1+i);
    }
    return 0;
}