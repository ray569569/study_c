#include <iostream>
using namespace std;

int Pow(int number, int power) {
    int result = 1;
    for (int i = 0; i < power; ++i) {
        result *= number;
    }
    return result;
}   

int main() {
    int number;
    cout << "Enter a positive integer: ";
    cin >> number;

    for (int i = 1; i <= 10; ++i) {
        cout << number << "^" << i << " = " << Pow(number, i) << endl;
    }

    return 0;
}
