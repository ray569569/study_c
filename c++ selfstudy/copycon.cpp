#include<iostream>
using namespace std;

class vec
{
private:
    int* arr;
    int len;
public:
    int getarr(int i)
    {
        return arr[i];
    }
    void setvalue(int x,int i)
    {
        arr[i]=x;
    }
    int getlen()
    {
        return len;
    }
    vec(int l)
    {
        len = l;
        arr = new int[len];
    }
    vec(const vec &a):len(a.len)
    {
        arr = new int[len];
        for(int i=0;i<len;i++)
        {
            arr[i]=a.arr[i];
        }
    }
    ~vec()
    {
        delete [] arr;
    }
};
int main()
{
    vec p1(10);
    for(int i=0;i<p1.getlen();i++)
    {
        p1.setvalue(i+1,i);
    }
    /*for(int i=0;i<p1.getlen();i++)
    {
        cout<<p1.getarr(i)<<endl;
    }
    */
    vec p2(p1);
    for(int i=0;i<p2.getlen();i++)
    {
        cout<<p2.getarr(i)<<endl;
    }
    return 0;
}