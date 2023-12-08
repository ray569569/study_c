#include<iostream>
#include<vector>
using namespace std;
template<class T>
class t
{
    protected:
        T a=10;
    
};
template<class T>
class child:public t<T> 
{

};
int main()
{
    
}