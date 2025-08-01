#include <iostream>
using namespace std;

int main() {
    for (char i = 'A'; i <= 'G'; i++) {
        for (int j = 1; j <= i - 64; j++) {
            cout << i ;
        }
        cout<<endl;
    }
    return 0;
}