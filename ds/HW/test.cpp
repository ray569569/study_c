#include<iostream>
#include<vector>
#include<cmath>
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
};

void swap(vegi &p1, vegi &p2){
    vegi temp = p1;
    p1 = p2;
    p2 = temp;
}

void buildheap(vector<vegi > &list)
{
    for(int i=list.size()-1;i>1;i--)
    {
        if(list[i/2].bundif<list[i].bundif)
        {
            //cout<<list[i/2].bundif<<" "<<list[i].bundif<<endl;
            swap(list[i/2],list[i]);
        }
    }
}

void heapsort(vector<vegi > &list)
{
    for(int i=1;i*2+1<list.size();)
    {
        if(list[i].bundif>=list[i*2].bundif&&list[i].bundif>=list[i*2+1].bundif)
        {
            break;
        }
        else
        {
            if(list[i*2].bundif>list[i*2+1].bundif)
            {
                swap(list[i*2],list[i]);
                i = i*2;
            }
            else
            {
                swap(list[i*2+1],list[i]);
                i = i*2+1;
            }
        }
    }
}

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
    vegi temp1(arr1[0],arr2[0]);
    list.push_back(temp1);
    for(int i=0;i<num;i++)
    {
        vegi temp(arr1[i],arr2[i]);
        list.push_back(temp);
    }

    buildheap(list);
    /*
    for(int i=1;i<=num;i++)
    {
        cout<<list[i].bunni1<<' '<<list[i].bunni2<<endl;
    }
    cout<<"ss"<<endl;
    */
    for(int i=1;i<=num;i++)
    {
        swap(list[1],list[list.size()-1]);
        sorted.push_back(list[list.size()-1]);
        //cout<<sorted[i-1].bundif<<endl;
        list.pop_back();
        heapsort(list);
    }
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