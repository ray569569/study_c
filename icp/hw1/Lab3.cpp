#include <iostream>
using namespace std;

int main() {
    int i = 210;
    while (i >= 10) {
        cout << i;
        i -= 1;
        if(i % 20 == 0) 
            cout << endl;
        else 
            cout << " ";
    }
    return 0;
}