#include<iostream>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

void rec(vector<int>,int a,int b);
int n;
int sum=0;
int main()
{
    cin >>n;
    vector<int> vec;
    for(int i=1;i<=n;i++)
    {
        vec.push_back(i);
    }
    rec(vec,0,n);
    cout<<sum<<endl;
    return 0;
}

void rec(vector<int> vec,int a,int b)
{
    if(a == b)
    {
        for(int i=0;i<n;i++)
        {
            cout<<vec[i];
        }

        cout<<endl;
        sum++;
    }
    else
    {
        for(int j=a;j<n;j++)
        {
            swap(vec[a],vec[j]);
            rec(vec,a+1,b);
            swap(vec[a],vec[j]);
        }
    }
}