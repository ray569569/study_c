#include<iostream>
using namespace std;

int main()
{
    int input;
    cout<<"please enter a number: ";
    cin>>input;
    switch (input)
    {
    case 11:
        cout<<"eleven"<<endl;
        break;
    case 12:
        cout<<"twelve"<<endl;
        break;
    case 13:
        cout<<"thirteen"<<endl;
        break;
    case 14:
        cout<<"fourteen"<<endl;
        break;
    case 15:
        cout<<"fifteen"<<endl;
        break;
    case 16:
        cout<<"sixteen"<<endl;
        break;
    case 17:
        cout<<"seventeen"<<endl;
        break;
    case 18:
        cout<<"eighteen"<<endl;
        break;
    case 19:
        cout<<"nineteen"<<endl;
        break;
    case 20:
        cout<<"twenty"<<endl;
        break;
    default:
        cout<<"invalid input"<<endl;
        break;
    }
    return 0;
}