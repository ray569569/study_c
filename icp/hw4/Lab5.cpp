#include<iostream>
#include<iomanip>
using namespace std;

int main()
{

    double startingBalance;
    cout << "Enter the starting balance: ";
    cin >> startingBalance;
    if (startingBalance < 0)
    {
        cout << "Invalid starting balance." << endl;
        return 1;
    }
    double annualInterestRate;
    cout << "Enter the annual interest rate: ";
    cin >> annualInterestRate;
    if (annualInterestRate < 0)
    {
        cout << "Invalid annual interest rate." << endl;
        return 1;
    }
    double balance = startingBalance;
    double totalDeposits = 0;
    double totalWithdrawals = 0;
    double totalInterest = 0;
    for (int i = 0; i < 3; i++)
    {
        double deposits;
        cout << "Enter the total amount deposited during month " << i + 1 << ": ";
        cin >> deposits;
        if (deposits < 0)
        {
            cout << "Invalid amount deposited." << endl;
            i--;
        }
        else
        {
            totalDeposits += deposits;
            balance += deposits;
        }
        double withdrawals;
        cout << "Enter the total amount withdrawn during month " << i + 1 << ": ";
        cin >> withdrawals;
        if (withdrawals < 0 || withdrawals > balance)
        {
            cout << "Invalid amount withdrawn." << endl;
            i--;
        }
        else
        {
            totalWithdrawals += withdrawals;
            balance -= withdrawals;
        }
        double monthlyInterestRate = annualInterestRate / 12;
        double interest = monthlyInterestRate * (startingBalance + balance) / 2;
        totalInterest += interest;
        balance += interest;
    }
    cout << "Starting balance: " << startingBalance << endl;
    cout << "Total deposits: " << totalDeposits << endl;
    cout << "Total withdrawals: " << totalWithdrawals << endl;
    cout << "Total interest: " << totalInterest << endl;
    cout << "Final balance: " << balance << endl;
    return 0;
}