#include<iostream>
using namespace std;

void hanai(int n, char a, char b, char c, int &count)
{
    if(n == 1)
    {
        cout<<"Move disk 1 from "<<a<<" to "<<c<<endl;
        count++;
    }
    else
    {
        hanai(n-1,a,c,b,count);
        cout<<"Move disk "<<n<<" from "<<a<<" to "<<c<<endl;
        count++;
        hanai(n-1,b,a,c,count);
    }
}

int main()
{
    int n;
    int count=0;
    for(int i=0;i<4;i++)
    {
        cin>>n;
        if(n%2 == 0)
        {
            hanai(n,'A','B','C',count);
            cout<<"Total moves: "<<count<<endl;
        }
        else 
        {
            hanai(n,'A','C','B',count);
            cout<<"Total moves: "<<count<<endl;
        }
        count =0;
    }
    return 0;
}