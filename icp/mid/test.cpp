#include<iostream>
#include<string>
#include<iomanip>
#include<ctime>
#include<cstdlib>
using namespace std;

int main()
{
    srand(time(0));
    int input=0;
    int n = rand()%5;
    float d = 5.3;
    string test = "abcde";
    printf("ass,%6.2f", d);
    cout<<fixed<<setprecision(2)<<d<<endl;
    cout<<setw(5);
    
    test.insert(0,"rr");
    cout<<test<<endl;
    test.erase(2,2);
    cout<<test;

    return 0;


}