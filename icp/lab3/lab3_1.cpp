#include<iostream>
using namespace std;

int main()
{
    int a,b,c;
    int i=0;
    do
    {
        i++;
        cout<<"please enter three numbers of angle: ";
        cin>>a>>b>>c;
        if(a+b+c!=180)
        {
            cout<<"The triangle is not valid"<<endl;
        }
        else if(a>90||b>90||c>90)
        {
            cout<<"Obtuse triangle"<<endl;
        }
        else if(a==90||b==90||c==90)
        {
            cout<<"Right angle triangle"<<endl;
        }
        else
        {
            cout<<"Acute triangle"<<endl;
        }
    }while(i<5);
    return 0;
}