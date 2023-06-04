#include<iostream>
#include<vector>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    int sum =0;
    vector<int > temp;
    vector<vector<int> > vec(12,vector<int>(12));
    
    for(int i=0;i<12;i++)
    {
        {
            for(int j=0;j<10;j++)
            vec[i][j] = sum++;
        }    
        
    }
    
    for(int i=0;i<12;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}

