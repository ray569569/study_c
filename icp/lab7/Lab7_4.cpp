#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

void permutate(string line, vector<string > &v)
{
    if(line.size() == 1)
    {
        v.push_back(line);
        cout<<line<<endl;
    }
    else
    {
        
        if(line.size()-1>0)
            permutate(line.substr(0,line.size()-1), v);
        int n = v.size();
        string temp = line.substr(line.size()-1,1);
        cout<<temp<<endl;
        v.push_back(temp);
        for(int i=0;i<n;i++)
        {
            cout<<v[i] + line[line.size()-1]<<endl;
            v.push_back(v[i] + line[line.size()-1]);
        }
    }
}

int main()
{
    ifstream in;
    in.open("Lab7_4.txt");
    string line;
    in>>line;
    vector<string> v;
    permutate(line, v);
    return 0;
}