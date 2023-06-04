#include<iostream>
#include<set>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

class Set
{
private:
    set<string> l;
public:
    void setvalue(vector<string> arr)
    {
        for(int i=0;i<arr.size() ;i++)
        {
            l.insert(arr[i]);
        }    
    }
    void printset()
    {
        
        set<string>::iterator t=l.begin();
        for(int i=0;i<l.size();i++)
        {
            cout<<*t<<endl;
            t++;
        }
    }
};

int main()
{
    string key;
    ifstream in;
    in.open("input.txt");
    vector<string> ver;
    while(!in.eof())
    {
        getline(in,key);
        ver.push_back(key);
    }

    Set f;
    f.setvalue(ver);
    f.printset();
    return 0;
}