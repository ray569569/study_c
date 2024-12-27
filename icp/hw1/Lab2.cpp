#include <iostream>
using namespace std;

int main() {
    int dollar, quarter, dime, nickel, penny;
    dollar = 5;
    quarter = 4;
    dime = 2;
    nickel = 3;
    penny = 8;
    cout << dollar * 100 + quarter * 25 + dime * 10 + nickel * 5 + penny << endl;
    return 0;
}


