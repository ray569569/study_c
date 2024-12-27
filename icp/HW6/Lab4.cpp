#include<iostream>
#include<vector>
#include<string>
using namespace std;

int main()
{
    vector<int> idx;
    string line;
    cin>>line;
    for(int i=0;i<line.size();i++)
    {
        if(line[i] <= 'Z')
        {
            idx.push_back(i);
        }
    }
    int count = 1;
    for(int i=0;i<line.size();i++)
    {
        
        if(i == idx[count] )
        {
            count++;
            cout<<" ";
        }
        cout<<line[i];
    }
    return 0;
}