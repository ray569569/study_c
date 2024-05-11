#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class item
{
public:
    int first;
    int second;
    item(int a,int b)
    {
        first=a;
        second=b;
    }
    bool friend operator<(item a,item b)
    {
        if(a.first<b.first)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
};

int main()
{
    int m,n,temp1,temp2;
    cin>>m>>n;
    vector<item > list;
    vector<int > target;
    for(int i=0;i<m;i++)
    {
        cin>>temp1>>temp2;
        item t(temp1,temp2);
        list.push_back(t);
    }
    for(int i=0;i<n;i++)
    {
        cin>>temp1;
        target.push_back(temp1);
    }
    sort(list.begin(),list.end());
    int out=0;
    for(int i=0;i<target.size();i++)
    {
        for(int j=0;j<list.size();j++)
        {
            if(target[i]>=list[j].first)
            {
                out = max(out,list[j].second);
            }
        }
        cout<<out<<' ';
        out = 0;
    }
    return 0;
}