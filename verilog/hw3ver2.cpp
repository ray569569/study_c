#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int main()
{
    int ten,five,one;
    for(int i=0;i<100;i++)
    {
        
        ten = i/10;
        if(i%10>=5)
        {
            five=1;
            one=i%10-5;
        }
        else
        {
            five=0;
            one = i%10;
        }
        //out<<temp<<" "<<total<<endl;
        //cout<<2*(temp[9]-48)<<endl;
        //cout<<((temp[0]-48)*4+(temp[1]-48)*2+temp[2]-48)<<endl;
        cout<<"7'd"<<i<<":begin one="<<one<<";five="<<five<<";ten="<<ten<<"; end"<<endl;
    }
    return 0;
}