#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "aaaaa";
    s.insert(3, 1, 'd');
    cout << s;
    return 0;
}