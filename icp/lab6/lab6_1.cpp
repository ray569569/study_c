#include<iostream>
#include<ctime>
using namespace std;

int main()
{
    srand(0);
    int n = 6;
    
    int** ptr = new int*[n]; //column
    for(int i=0;i<n;i++)
    {
        ptr[i] = new int[n]; //row
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            ptr[i][j] = rand()%6;
        }
    }   
    cout<<"Original Matrix"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<ptr[i][j]<<" ";
        }
        cout<<endl;
    }
    int sum_arr[n];
    for(int i=0;i<n;i++)
    {
        int sum = 0;
        for(int j=0;j<n;j++)
        {
            sum += ptr[i][j];
        }
        sum_arr[i] = sum;
    }

    
    pair<int,int> arr[6];
    for(int i=0;i<n;i++)
    {
        arr[i].first = sum_arr[i];
        arr[i].second = i;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(arr[i].first<arr[j].first)
            {
                swap(arr[i],arr[j]);
            }
        }
    }
    cout<<"Organized Matrix"<<endl;
    int temp[n][n];
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            temp[i][j] = ptr[arr[i].second][j];
        }
    }


    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<temp[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=0;i<n;i++)
    {
        int sum = 0;
        for(int j=0;j<n;j++)
        {
            sum += temp[i][j];
        }
        cout<<sum<<" ";
    }
    
    return 0;
}