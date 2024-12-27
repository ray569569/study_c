#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
using namespace std;

int main() {
    float a, b, c;
    cin >> a >> b >> c;
    if (a < 100 || a > 500 || b < 100 || b > 500 || c < 100 || c > 500) {
        cout << "Please input number between 100 and 500" << endl;
        return 0;
    }
    float sum = (a + b) * c;
    cout << std::scientific <<std::uppercase<< std::setprecision(2) << sum << endl;
}