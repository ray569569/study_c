#include <iostream>
using namespace std;

int main() {
    string in;
    int count;
    cin >> in;
    for (int i = 0; i < in.length(); i++) {
        if (in[i] == 'a' || in[i] == 'e' || in[i] == 'i' || in[i] == 'o' || in[i] == 'u') {
            count++;
        }
    }
    cout << count << endl;
}