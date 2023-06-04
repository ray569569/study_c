#include<iostream>
#include<sstream>
using namespace std;

int main()
{
    long int sum=0;
    int temp;
    string line="";
    stringstream ss1;
    while(getline(cin,line))
    {
        while(ss1<<line)
        {
            ss1 >> temp;
            sum += temp;
        }
        cout << sum <<endl;
        sum = 0;
        line = "";
    }
    return 0;
}

