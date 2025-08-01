#include<iostream>
#include<vector>
#include<fstream>
#include<random>
using namespace std;

int main() 
{
    fstream file;
    fstream file1;
    file.open("input.txt", ios::out);
    file1.open("output.txt", ios::out);
    double x;
    for(int i=0;i<100000;i++)
    {
        x = static_cast<double>(rand()) / RAND_MAX * 6;
        file << int(x*4096) << endl;
    
        if(x < 1)
        {
            file1 << int(x*4096 / 2)<<endl;
        }
        else
        {
            file1 << int((1 - 1 / (2 * x))*4096)<<endl;
        }
    }
    return 0;
}