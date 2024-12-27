#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

int main()
{
    ifstream in;
    in.open("Lab7_1.txt");
    string line;
    stringstream ss1;

    vector<vector<int>> v;
    vector<int> v1;
    while(!in.eof())
    {
        
        getline(in, line);
        ss1 << line;
        int temp;
        while(ss1 >> temp)
        {
            v1.push_back(temp);
        }
        ss1.clear();
        v.push_back(v1);
        v1.clear();
    }
    cout<<"Local Maxima: "<<endl;   
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < v[i].size(); j++)
        {
            if(0<=i-1 && v[i-1][j] >= v[i][j])
            {
                continue;
            }
            if(0<=j-1 && v[i][j-1] >= v[i][j])
            {
                continue;
            }
            if(i+1<v.size() && v[i+1][j] >= v[i][j])
            {
                continue;
            }
            if(j+1<v[i].size() && v[i][j+1] >= v[i][j])
            {
                continue;
            }
            cout <<"Value: "<< v[i][j] << " at ("<< i+1 << ", " << j+1 <<")"<< endl;
        }
    }
    return 0;
    
}