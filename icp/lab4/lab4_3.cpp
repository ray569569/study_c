#include <iostream>
using namespace std;

int GCD(int A, int B);
int main() {
    for (int i = 0; i < 5; i++) {
        int A, B;
        cout << "Enter two numbers: ";
        cin >> A >> B;
        if(A>B)
            cout << GCD(A, B) << endl;
        else
            cout << GCD(B, A) << endl;
    }
    return 0;
}

int GCD(int A, int B) {
    if (A % B != 0)
        return GCD(B, A % B);
    else
        return B;
}