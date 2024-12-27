#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./test/lab2/text8.txt");
    string line;
    getline(in, line);

    string max = "";

    for (int i = 0; i < line.size(); i++) {
        string temp = "";
        for (int j = i; j < line.size(); j++) {
            if (islower(line[j])) {
                temp = temp + line[j];
            } else if (isupper(line[j])) {
                temp = temp + line[j];
            } else {
                break;
            }
        }
        if (temp.size() > max.size()) {
            max = temp;
        }
    }

    cout << max;
    return 0;
}