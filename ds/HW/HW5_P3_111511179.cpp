#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    int left, right, num, maxlength;
    cin>>left>>right>>num;
    vector<int > resvered;
    for(int i=0;i<num;i++)
    {
        int temp;
        cin>>temp;
        resvered.push_back(temp);
    }
    sort(resvered.begin(),resvered.end());
    //cout<<resvered[0] - left<<' '<<right - resvered[num-1]<<endl;
    maxlength = max(resvered[0] - left, right - resvered[num-1]);
    for(int i=0;i<num-1;i++)
    {
        maxlength = max(maxlength, resvered[i+1] - resvered[i]-1);
    }
    cout<<maxlength;
    return 0;
}