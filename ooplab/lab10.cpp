#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<fstream>
using namespace std;
vector<string> Pair(vector<string> x);

int main(int argc,char** argv)
{
    vector<string > a;
    ifstream in;
    in.open("input.txt");
    while(!in.eof())
    {
        string b;
        in>>b;
        a.push_back(b);
    }
    vector<string> p = Pair(a);
    vector<string>::iterator f = p.begin();
    for(int i=0;i<p.size();i++)
    {
        cout<<*f<<" ";
        f++;
    }
    cout<<endl;
    sort(p.begin(),p.end());
    f=p.begin();
    for(int i=0;i<p.size();i++)
    {
        cout<<*f<<" ";
        f++;
    }

    return 0;
}

vector<string> Pair(vector<string> x)
{
    vector<string>::iterator y = x.begin();
    vector<string>::iterator z = x.begin();
    for(int i=0;i<x.size();i++)
    {
        for(int j=i+1;j<x.size();j++)
        {
            z = x.begin();
            z = z+j;
            if(*y == *z)
            {
                
                x.erase(y);
                x.erase(z);
            }

        }
        y++;
    }
    return x;
}