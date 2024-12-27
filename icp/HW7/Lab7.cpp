#include <iostream>
#include <cmath>
using namespace std;

class EMI
{
private:
    double loanAmount;
    double annualInterestRate;
    int loanRepaymentPeriod;

public:
    void input()
    {
        cout << "Amount of loan :";
        cin >> loanAmount;
        cout << "Yearly Interest Rate :";
        cin >> annualInterestRate;
        cout << "Years for Loan Repayment :";
        cin >> loanRepaymentPeriod;
    }
    double calculateEMI()
    {
        double monthlyInterestRate = annualInterestRate / 12;
        int totalInstallments = 12 * loanRepaymentPeriod;
        return loanAmount * monthlyInterestRate * pow((1 + monthlyInterestRate), totalInstallments) / (pow((1 + monthlyInterestRate), totalInstallments) - 1);
    }
};

int main()
{
    EMI e1;
    char choice;
    do
    {
        e1.input();
        cout << "EMI payable = " << e1.calculateEMI() << endl;
        cout << "Do you want to find another EMI: ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    return 0;
}