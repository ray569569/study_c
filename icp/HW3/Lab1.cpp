#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    cout << "Enter numerator and denominator of first fraction: ";
    cin >> a >> b;
    cout << "Enter numerator and denominator of second fraction: ";
    cin >> c >> d;

    cout << "Sum of the fractions: " << a * d + b * c << "/" << b * d << endl;
    return 0;
}
