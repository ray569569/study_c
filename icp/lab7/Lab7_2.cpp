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

    cout<<"Corner element: "<<endl;   
    for(int i = 0; i < v.size(); i++)
    {
        for(int j = 0; j < v[i].size(); j++)
        {
            if(i == 0 || i == v.size()-1 || j == 0 || j == v[i].size()-1)
            {
                cout<<v[i][j]<<" ";
            }
        }
    }
    return 0;
}