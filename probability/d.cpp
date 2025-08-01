#include<cstdlib>
#include<cmath>
#include<iostream>
#include<ctime>
using namespace std;

int main()
{
    const double pi=3.1415926;
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
        //cout<<cos(pi*x)+sin(pi*y)<<endl;
        if(0<=cos(pi*x)+sin(pi*y)&&cos(pi*x)+sin(pi*y)<=1)
        {
            s = s*(double(i-1))/(double(i))+1.0/double(i);
        }
        else
        {
            s = s*(double(i-1))/(double(i));
        }
    }
    cout<<s<<endl;
}