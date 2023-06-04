#include<iostream>
#include"func.h"

using namespace std;
int main()
{
    int n1,n2;
    int* a1;
    int* a2;

    cin>>n1;
    a1 = new int[n1];
    for(int i=0;i<n1;i++)
    {
        cin>>a1[n1-i-1];
        
    }
    cin>>n2;
    a2 = new int[n2];
    for(int i=0;i<n2;i++)
    {
        cin>>a2[n2-i-1];
        
    }

    PolySeq f1(a1,n1);
    PolySeq f2(a2,n2);
    
    int c,d;
    float e;
    cin>>c>>d>>e;

    int sum=0;
    sum = Poly_int::getvalue(f1,c) + Poly_int::getvalue(f2,c);
    float der=0;
    PolySeq temp =  f1.Derivative();
    //cout<<temp.num<<endl;
    
    der = Poly_float::getvalue(temp,1.3);
    int in;

    in = f2.integral(c,d);
    cout<<sum<<endl<<der<<endl<<in<<endl;
    return 0;
}