#include<iostream>
using namespace std;

bool isRelativePrime(int a, int b)
{
    for (int i = 2; i <= a && i <= b; i++)
    {
        if (a % i == 0 && b % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int a, b;
    cout << "Enter two positive numbers: ";
    cin >> a >> b;
    if (a <= 0 || b <= 0)
    {
        cout << "Invalid numbers." << endl;
        return 1;
    }
    if (isRelativePrime(a, b))
    {
        cout << "The numbers are relatively prime." << endl;
    }
    else
    {
        cout << "The numbers are not relatively prime." << endl;
    }
    return 0;
}