#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

int main()
{
    string line;
    getline(cin,line);
    stringstream ss(line);
    vector<string> words;
    string word;
    while(ss>>word)
    {
        words.push_back(word);
    }
    for(int i=0;i<words.size();i++)
    {
        for(int j=0;j<words[i].size();j++)
        {
            if(words[i][j]>='a' && words[i][j]<='z' && i==0 &&j==0)
                words[i][j] = words[i][j]-32;
            if(words[i][j]>='A' && words[i][j]<='Z' && (i!=0 || j!=0))
                words[i][j] = words[i][j]+32;
        }
        if(i>0 && words[i-1][words[i-1].size()-1]=='.')
            words[i][0] = words[i][0]-32;
        cout<<words[i]<<" ";
    }
    return 0;
}