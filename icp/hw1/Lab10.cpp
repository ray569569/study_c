#include <iostream>
using namespace std;

int main() {
    int num1, num2, num3, num4;
    double mean, variance, stddev;

    cout << "Enter four integers: ";
    cin >> num1 >> num2 >> num3 >> num4;

    mean = (num1 + num2 + num3 + num4) / 4.0;

    variance = (((num1 - mean) * (num1 - mean) +
                 (num2 - mean) * (num2 - mean) +
                 (num3 - mean) * (num3 - mean) +
                 (num4 - mean) * (num4 - mean)) /
                4.0);

    stddev = variance;  
    for (int i = 0; i < 10; ++i) {
        stddev = 0.5 * (stddev + variance / stddev); 
    }

    cout << "Mean: " << mean << endl;
    cout << "Standard Deviation: " << stddev << endl;
    return 0;
}
