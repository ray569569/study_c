#include<iostream>
using namespace std;

int main()
{
    sort(mMyClassVector.begin(), mMyClassVector.end(), 
    [](const MyClass & a, const MyClass & b)
{ 
    return a.mProperty > b.mProperty; 
});
}