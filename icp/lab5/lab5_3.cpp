#include <iostream>
using namespace std;

int main() {
    for (int i = 3; i <= 21; i += 2) {
        for (int j = 0; j < i; j++) {
            for (int k = 1; k <= i; k++) {
                if(j==i/2)
                {
                    cout << "+";
                }
                else if((k<=(j+i/2+1) &&k>=(i/2+1))&&(j<=i/2)||(k<=(i-j+i/2) && k>=(i/2+1))&&(j>i/2))
                    cout << "+";
                else
                    cout << " ";
            }
            cout << endl;
        }
        cout << "------------------------------" << i << endl;
    }
    return 0;
}