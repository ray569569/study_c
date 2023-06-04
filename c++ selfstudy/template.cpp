#include<iostream>
using namespace std;


template<class ty=int ,int size=10>
class test
{
private:
    ty a;
    ty arr[size];
public:
    void setvalue(ty x);
    ty getvalue();
    void setarr();
    void getarr()
    {
        for(int i=0;i<size;i++)
        {
            cout<<arr[i]<<endl;
        }
    }
};
template<class ty,int size>
void test< ty,size >::setvalue(ty x)
{
    a = x;
    return ;
}
template<class ty,int size >
ty test< ty,size>::getvalue()
{
    return a;
}
template<class ty,int size>
void test<ty,size>::setarr()
{
    for(int i=0;i<size;i++)
    {
        arr[i] = i;
    }
}
int main()
{
    test<> f;
    f.setvalue(500);
    cout<<f.getvalue()<<endl;
    f.setarr();
    f.getarr();
    return 0;
}