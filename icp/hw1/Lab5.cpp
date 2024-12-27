#include <cmath>
#include <iostream>
using namespace std;

int main() {
    int a = 1, b = 1;
    while (a < 30000 || b < 30000) {
        cout << b << " ";
        int c;
        c = a;
        a = a + b;
        b = c;
    }
}
