#include<iostream>
using namespace std;

int main()
{
    int n;
    int pos = 0;
    int neg = 0;
    cout << "Enter a positive number: ";
    cin >> n;
    int i = 0;
    while (i < n)
    {
        int num;
        cout << "Enter a number: ";
        cin >> num;
        if (num > 0)
        {
            pos++;
        }
        else if (num < 0)
        {
            neg++;
        }
        i++;
    }
    cout << "Total positive numbers: " << pos << endl;
    cout << "Total negative numbers: " << neg << endl;
    return 0;
}