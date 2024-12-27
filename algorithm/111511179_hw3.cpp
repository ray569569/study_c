#include<iostream>
#include<vector>

using namespace std;

void cal_cost(int step, vector<int > &result, vector<int> cost)
{
    if(step == 0)
    {
        result.push_back(cost[0]);
    }
    else if(step == 1)
    {
        result.push_back(cost[1]);
    }
    else if(step == 2)
    {
        result.push_back(cost[2] + result[1]);
    }
    else
    {
        int temp = cost[step] + min(result[step-3], result[step-1]);
        result.push_back(temp);
    }
}

int main()
{
    vector<int> cost;
    int temp;
    while(cin>>temp)
    {
        cost.push_back(temp);
    }
    
    int n = cost.size();
    vector<int> result;
    for(int i=0;i<n;i++)
    {
        cal_cost(i, result, cost);
    }
    if(n == 1)
    {
        cout<<result[0];
        return 0;
    }
    else if(n == 2)
    {
        cout<<min(result[0],result[1]);
        return 0;
    }
    else 
    {
        cout<<min(result[n-3],min(result[n-1],result[n-2]));
        return 0;
    }
    
}