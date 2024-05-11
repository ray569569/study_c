#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

class vegi
{
public:
    int bunni1;
    int bunni2;
    int bundif;
    vegi(int a,int b)
    {
        bunni1 = a;
        bunni2 = b;
        bundif = a-b;
    }
    bool friend operator <(vegi a,vegi b)
    {
        if(a.bundif<b.bundif)
        {
            return false;
        }
        else 
        {
            return true;
        }
    }
};

int main()
{
    vector<vegi > list;
    vector<vegi > sorted;
    int num,first;
    int* arr1;
    int* arr2;
    cin>>num;
    arr1 = new int[num];
    arr2 = new int[num];
    for(int i=0;i<num;i++)
    {
        cin>>arr1[i];
    }
    for(int i=0;i<num;i++)
    {
        cin>>arr2[i];
    }
    cin>>first;
    for(int i=0;i<num;i++)
    {
        vegi temp(arr1[i],arr2[i]);
        list.push_back(temp);
    }

    sorted = list;
    //cout<<sorted.size()<<endl;
    sort(sorted.begin(),sorted.end());
    int sum=0;
    for(int i=0;i<sorted.size();i++)
    {
        if(i<first)
        {
            sum+=sorted[i].bunni1;
        }
        else
        {
            sum+=sorted[i].bunni2;
        }
    }
    cout<<sum<<endl;
    return 0;
}