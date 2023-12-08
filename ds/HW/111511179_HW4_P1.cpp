#include<iostream>
#include<map>
#include<string>
#include<sstream>
#include<vector>
using namespace std;

class Gate
{
public:
    string type;
    string input1;
    string input2;
    string output;
    Gate(string t,string in1,string in2,string out)
    {
        type = t;
        input1 = in1;
        input2 = in2;
        output = out;
    }
};
int main()
{
    map<string, bool> list;
    string input, input1, gate, in1, in2, out;
    vector<string > ans;
    vector<Gate > gatelist;
    int temp1=0;

    getline(cin,input);
    getline(cin,input1);
    stringstream ss, tt;
    ss << input;
    tt << input1;
    while (ss >> in1) {
        tt >> temp1;
        list[in1] = temp1;
    }

    getline(cin,input);
    stringstream kk;
    kk<<input;
    while(kk>>in1)
    {
        ans.push_back(in1);
    }

    while(getline(cin,input))
    {
        stringstream mm;
        mm<<input;
        mm>>gate;
        mm>>in1;
        if(gate=="INV")
        {
            mm>>in1;
            mm>>out;
            Gate temp(gate,in1,in1,out);
            gatelist.push_back(temp);
        }
        else if(gate=="NAND"||gate=="NOR")
        {
            mm>>in1;
            mm>>in2;
            mm>>out;
            Gate temp(gate,in1,in2,out);
            gatelist.push_back(temp);
        }
    }

    for(int i=0;i<gatelist.size();i++)
    {
        for(int j=0;j<gatelist.size();j++)
        {
            map<string, bool >::iterator iter1 = list.find(gatelist[j].input1);
            map<string, bool >::iterator iter2 = list.find(gatelist[j].input2); 
            if(iter1!=list.end()&&iter2!=list.end())
            {
                if(gatelist[j].type == "INV")
                {
                    list[gatelist[j].output]=!list[gatelist[j].input1];
                }
                else if(gatelist[j].type=="NAND")
                {
                    list[gatelist[j].output] = !(list[gatelist[j].input1]&&list[gatelist[j].input2]);
                }
                else if(gatelist[j].type=="NOR") 
                {
                    list[gatelist[j].output] = !(list[gatelist[j].input1]||list[gatelist[j].input2]);
                }
            }
        }
    }
    int n=0;
    while(n<ans.size())
    {
        cout<<ans[n]<<" "<<list[ans[n]]<<endl;
        n++;
    }
    return 0;
}