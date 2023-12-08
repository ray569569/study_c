#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

int main()
{
    map<string, bool> list;
    string input,input1;
    string gate, key, key1, key2;
    vector<string > ans;
    int temp1=0;
    getline(cin,input);
    getline(cin,input1);

    stringstream ss, tt;
    ss << input;
    tt << input1;

    while (ss >> key) {
        tt >> temp1;
        list[key] = temp1;
    }
    getline(cin,input);
    //cout<<"dd"<<" "<<input<<endl;
    stringstream kk;
    kk<<input;
    while(kk>>key)
    {
        //cout<<"rr";
        list[key]=0;
        ans.push_back(key);
    }
    while(getline(cin,input))
    {
        stringstream mm;
        mm<<input;
        //cout<<input<<endl;  
        mm>>gate;
        //cout<<gate<<endl;
        mm>>key;
        //cout<<key<<endl;
        if(gate=="INV")
        {
            mm>>key;
            mm>>key1;
            list[key1]=!list[key];
        }
        else if(gate=="NAND")
        {
            mm>>key;
            mm>>key1;
            mm>>key2;
            list[key2] = !(list[key]&&list[key1]);
        }
        else if(gate=="NOR")
        {
            mm>>key;
            mm>>key1;
            mm>>key2;
            list[key2] = !(list[key]||list[key1]);
        }
    }
    int n=0;
    /*
    for(auto i:list)
    {
        cout<<i.first<<' '<<i.second<<endl;
    }*/
    while(n<ans.size())
    {
        //cout<<"ss";
        cout<<ans[n]<<" "<<list[ans[n]]<<endl;
        n++;
    }
    return 0;
}