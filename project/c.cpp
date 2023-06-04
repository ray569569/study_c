#include<cstdlib>
#include<cmath>
#include<iostream>
#include<ctime>
using namespace std;

int main()
{
    srand( time(NULL) );
    double s=0.0;
    for(int i=1;i<=10000;i++)
    {
        double x = rand();
        double y = rand();
        //cout<<x<<endl<<y<<endl;
        x/=double(RAND_MAX);
        y/=double(RAND_MAX);
        //cout<<x<<endl<<y<<endl;
        if((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5)<0.25)
        {
            s = s*(double(i-1))/(double(i))+1/double(i);
        }
        else
        {
            s = s*(double(i-1))/(double(i));
        }
    }
    cout<<s*4<<endl;
}