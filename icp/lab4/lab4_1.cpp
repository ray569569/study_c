#include <iostream>
#include<string>
using namespace std;

int sumfun(int n);
int main() {
    int  in ;
    for (int i = 0; i < 5; i++) {
        cout << "Enter a number: ";
        cin >> in;
        int sum = sumfun(in);
        cout << sum<<endl;
    }
    return 0;
}

int sumfun(int n) {
    if (n == 0)
        return 0;
    return 1 + sumfun(n / 10);
}