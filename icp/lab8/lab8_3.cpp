#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool check_find(string str, string sub) {
    for (int i = 0; i < str.size(); i++) {
        for (int j = 0; j < sub.size(); j++) {
            if (str[i] == sub[j]) {
                sub.erase(j, 1);
                break;
            }
        }
    }
    if (sub.size() == 0) {
        return true;
    }
    return false;
}

int main() {
    ifstream in("./lab3/t8.txt");
    string line;
    string target;
    in >> target;
    in >> line;
    for (int i = 0; i < (line.size() - target.size() + 1); i++) {
        string sub = line.substr(i, target.size());
        if (check_find(sub, target)) {
            cout << "True" << endl;
            return 0;
        }
    }
    cout << "False" << endl;
    return 0;
}