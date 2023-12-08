#include "func.h"
#include<iostream>
using namespace std;
PolySeq::PolySeq(int* a,int b)
{
    num = b;
    coef = new int[b];
    for(int i=0;i<b;i++)
    {
        coef[i] = a[i];
    }
}
PolySeq::PolySeq()
{
    coef = new int[0];
    num = 0;
}
PolySeq PolySeq::Add(PolySeq a)
{
    PolySeq t;
    if(a.num>num)
    {
        t.num = a.num;
        t.coef = new int[t.num];
        for(int i=0;i<num;i++)
        {
            t.coef[i] = coef[i] + a.coef[i];
        }
        for(int i = num;i<t.num;i++)
        {
            t.coef[i] = a.coef[i];
        }
    }
    else 
    {
        t.num = num;
        t.coef = new int[t.num];
        for(int i=0;i<a.num;i++)
        {
            t.coef[i] = coef[i] + a.coef[i];
        }
        for(int i = a.num;i<t.num;i++)
        {
            t.coef[i] = coef[i];
        }
    }
    return t;
}
PolySeq PolySeq::Derivative()
{
    PolySeq t;
    if(num>1)
    {
        t.num = num-1;
    }
    else if(num == 1)
    {
        t.num = 1;
    }
    t.coef = new int[t.num];

    for(int i=0;i<t.num;i++)
    {
        t.coef[i] = coef[i+1] *(i+1);
    }
    return t;
}
int PolySeq::integral(int a,int b)
{
    PolySeq t;
    t.num = num+1;
    t.coef = new int[t.num];

    t.coef[0] =0;
    for(int i=0;i<num;i++)
    {
        t.coef[i+1] = coef[i]/(i+1);
    }
    /*
    for(int i=0;i<t.num;i++)
    {
        cout<<t.coef[i]<<endl;
    }
    */
    int sum;
    sum = Poly_int::getvalue(t,b) - Poly_int::getvalue(t,a);

    return sum;
}
int Poly_int::getvalue(PolySeq a,int b) 
{
    int sum=a.coef[0];
    int p=b;
    for(int i=1;i<a.num;i++)
    {
        sum += a.coef[i] * p;
        p=p*b; 
    }
    return sum;
}
float Poly_float::getvalue(PolySeq a,float b) 
{
    float sum=a.coef[0];
    float p=b;
    for(int i=1;i<a.num;i++)
    {
        sum += a.coef[i] * p;
        p=p*b; 
    }
    
    return sum;
}