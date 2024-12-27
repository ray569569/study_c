#include<iostream>
#include<vector>
using namespace std;

void quicksort(int left, int right, vector<int> &in);
void exchange(int &a,int &b);

int main()
{
    vector<int> input;
    int power,temp,grade=0,sum=0;

    cin>>power>>temp;
    while(temp!=-1)
    {
        input.push_back(temp);
        cin>>temp;
    }

    int length = input.size()-1;
    //cout<<length<<endl;
    quicksort(0,length,input);
    /*
    for(int i =0;i<=length;i++)
        cout<<input[i]<<' ';
        */
    sum+=power;
    for(int i=0;i<=length;i++)
        sum += input[i];
    
    if(power<input[0])
        cout<<'0';
    else
    {
        temp = sum/2;
        sum = power;
        for(int i=length;i>=0;i--)
        {
            if(sum+input[i]<=temp)
            {
                sum+=input[i];
            }
            else
            {
                grade -= (length-i);
                break;
            }
        }
        for(int i=0;i<=length;i++)
        {
            if(sum-input[i]>=0)
            {
                sum-=input[i];
            }
            else
            {
                grade +=i;
                break;
            }
        }
        cout<<grade;
    }
    return 0;
}

void quicksort(int left, int right, vector<int> &in)
{
    if(left<right)
    {
        int mid=left-1;
        for(int j=left;j<right;j++)
        {
            if(in[j]<=in[right])
            {
                exchange(in[j],in[mid+1]);
                mid++;
            }
        }
        mid++;
        exchange(in[right],in[mid]);
        quicksort(left, mid-1, in);
        quicksort(mid+1, right, in);
    }
}

void exchange(int &a,int &b)
{
    int c = a;
    a = b;
    b = c;
    return ;
}