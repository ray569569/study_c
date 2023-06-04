#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int search(vector<int > &vec,int a,int b,int x)
{
    int mid = (a+b)/2;
    if(a == b)
    return -1;
    else if(vec[mid]<x)
    {
        return search(vec,mid,b,x);
    }
    else if(vec[mid]>x)
    {
        return search(vec,a,mid,x);
    }
    else if(vec[mid])
    {
        return mid+1;
    }
    return -1;
}

int main()
{
    ifstream in;
    in.open("input.txt");
    vector<int > vec;
    int temp;
    while(in>>temp)
    {
        vec.push_back(temp);
    }
    sort(vec.begin(),vec.end());
    int n = vec.size();
    cout<<search(vec,0,n-1,100)<<endl;
    return 0;    
}
