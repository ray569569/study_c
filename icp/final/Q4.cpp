#include <cmath>
#include <fstream>
#include <iostream>
using namespace std;

bool isBaseB(long long, int);
long long B2dec(long long, int);

int main() {
    long long a;
    int b;

    ifstream file("./Q4/Q4_T10.txt");
    if (!file) {
        cout << "Error: Could not open file example.txt" << endl;
        return 1;
    }

    file >> a >> b;
    // To do list
    if (isBaseB(a, b)) {
        cout << "(" << a << "," << b << ")=" << B2dec(a, b) << endl;
    } else {
        cout << a << " is not " << b << " based" << endl;
    }

    file.close();
    return 0;
}

bool isBaseB(long long a, int b) {
    while (a > 0) {
        if (a % 10 < b)
            a /= 10;
        else
            return false;
    }
    return true;
}
long long B2dec(long long a, int b) {
    long long ans = 0;
    int exp = 1;
    while (a > 0) {
        ans += (a % 10) * exp;
        a /= 10;
        exp *= b;
    }
    return ans;
}
