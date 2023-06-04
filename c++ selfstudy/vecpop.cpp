#include<iostream>
#include<vector>
using namespace std;

int main()
{
    vector<int > vec;
    for(int i=0;i<10;i++)
    {
        vec.push_back(i);
    }
    for(int j=0;j<3;j++)
    {
        vec.pop_back();
    }
    for(int i=0;i<vec.size();i++)
    {
        cout<<vec[i]<<endl;
    }
    return 0;
}