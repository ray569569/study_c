#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./lab2/t8.txt");
    string line;
    in >> line;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] != line[line.size() - i - 1]) {
            cout << "False" << endl;
            return 0;
        }
    }
    cout << "True" << endl;
    return 0;
}