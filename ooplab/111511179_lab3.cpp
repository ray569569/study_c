#include<iostream>
using namespace std;

int sum=0;
int step=0;
string k;
void hanoi(int n, char a, char b, char c)
{
    if(n<=0)
        return ;
    hanoi(n-1,a,c,b);
    switch(n)
        {
            case 1:
                k = "first";
                break;
            case 2:
                k = "second";
                break;
            case 3:
                k = "third";
                break;
            case 4:
                k = "forth";
                break;
            case 5:
                k = "fifth";
                break;
            case 6:
                k = "stxth";
                break;
            case 7:
                k = "seventh";
                break;
            case 8: 
                k = "eighth";
                break;
            case 9:
                k = "ninth";
                break;
            case 10:
                k = "tenth";
                break;
        }
    cout<<"step"<<step++<<": move the "<<k<<" plate from "<<a<<" to "<<c<<endl;
    hanoi(n-1,b,a,c);

}

int main()
{
    int num;
    cout<<"the number of the plate: ";
    cin >> num;
    hanoi(num,'A','B','C');
    cout<<endl<<"Need to move "<<step<<" times"<<endl;
    return 0;

}