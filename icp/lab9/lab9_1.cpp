#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./test/lab1/text8.txt");
    string line;
    in >> line;
    vector<char> v;
    for (int i = 0; i < line.size(); i++) {
        bool duplicate = false;
        for (int j = 0; j < v.size(); j++) {
            if (line[i] == v[j]) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            continue;
        }
        v.push_back(line[i]);
    }
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
    }
    return 0;
}