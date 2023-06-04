#include<iostream>
#include<fstream>
using namespace std;

int cal1(int* b,int num1,int num2);
int cal2(int* b,int num1,int num2);
int n;
int size;
int main()
{
    ifstream in;
    in.open("input.txt");
    int num1,num2;
    in>>n>>size;

    int* a;
    a = new int[n];
    for(int i =0;i<n;i++)
    {
        in>>a[i];
    }

    int big=0;
    int biga,bigb;
    for(int k=0;k<size;k++)
    {

        in>>num1>>num2;
        
        num1-=1;
        num2-=1;
        
        if(num1<num2)
        {
            int t;
            t=cal1(a,num1,num2);
            if(t>big)
            {
                big = t;
                biga=num1;
                bigb=num2;
                
            }

        }
        else if(num1 == num2)
        {
            if(a[num1]>big)
            {
                big = a[num1];
                biga=num1;
                bigb=num2;
            }
        }
        else if(num1>num2)
        {
            int t;
            t=cal2(a,num1,num2);
            if(t>big)
            {
                big = t;
                biga=num1;
                bigb=num2;
            }
        }
    }
    cout<<"Max_range: ("<<biga+1<<","<<bigb+1<<"); Value: "<<big<<endl;
    return 0;


}
int cal1(int* b,int num1,int num2)
{
    int sum=0;
    for(int j=num1;j<=num2;j++)
    {
        sum += b[j];
    }
    return sum;
}
int cal2(int* b,int num1,int num2)
{
    int sum=0;
    for(int j=0;j<=num2;j++)
    {
        sum += b[j];
    }
    for(int j=num1;j<n;j++)
    {
        sum += b[j];
    }
    return sum;
}