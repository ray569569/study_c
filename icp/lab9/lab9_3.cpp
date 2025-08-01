#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int count(string a, string b) {
    if (a.size() == 0 || b.size() == 0) {
        return 0;
    }
    if (a[a.size() - 1] == b[b.size() - 1]) {
        return 1 + count(a.substr(0, a.size() - 1), b.substr(0, b.size() - 1));
    } else {
        return max(count(a.substr(0, a.size() - 1), b), count(a, b.substr(0, b.size() - 1)));
    }
}

int main() {
    ifstream in("./test/lab3/text8.txt");
    string a, b;
    getline(in, a);
    getline(in, b);

    cout << count(a, b);
    return 0;
}