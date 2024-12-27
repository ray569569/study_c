#include<iostream>
#include<string>
using namespace std;

int main()
{
    string in;
    cout<<"please input a sequence of number: ";
    cin>>in;
    int max=0;
    int temp = 0;
    for(int i=0;i<in.size();i++)
    {
        if(in[i]!=in[i+1])
        {
            temp+=(in[i] - '0');
        }
        else 
        {
            temp+=(in[i] - '0');
            if(max<=temp)
                max = temp;
            temp = 0;
        }
        if(i == in.size()-1)
        {
            if(max<=temp)
                max = temp;
        }
    }
    cout<<"max value is: "<<max<<endl;
    return 0;
}