#include<iostream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

int main()
{
    stringstream ss1;
    string line;
    getline(cin, line);
    ss1 << line;
    string word;
    vector<string> words;
    while (ss1 >> word)
    {
        words.push_back(word);
    }
    for(int i=0;i<words.size();i++)
    {
        cout<<words[i][0];
        if(i!=words.size()-1)
        {
            cout<<".";
        }
    }
    cout<<".";
    return 0;
}