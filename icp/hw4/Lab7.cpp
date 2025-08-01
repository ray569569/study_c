#include<iostream>
using namespace std;

double calcProfit(int NS, double PP, double PC, double SP, double SC)
{
    return ((NS * SP) - SC) - ((NS * PP) + PC);
}

int main()
{
    int NS;
    double PP, PC, SP, SC;
    cout << "Enter the number of shares: ";
    cin >> NS;
    cout << "Enter the purchase price per share: ";
    cin >> PP;
    cout << "Enter the purchase commission paid: ";
    cin >> PC;
    cout << "Enter the sale price per share: ";
    cin >> SP;
    cout << "Enter the sale commission paid: ";
    cin >> SC;
    double profit = calcProfit(NS, PP, PC, SP, SC);
    if (profit > 0)
    {
        cout << "Profit: $" << profit << endl;
    }
    else if (profit < 0)
    {
        cout << "Loss: $" << -profit << endl;
    }
    else
    {
        cout << "No profit or loss." << endl;
    }
    return 0;
}