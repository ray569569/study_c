#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./lab1/t8.txt");
    string line;
    in >> line;
    string ans;
    char target;
    int count = 0;
    target = line[0];
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == target) {
            count++;
        } else {
            ans += target;
            ans += to_string(count);
            target = line[i];
            count = 1;
        }
    }
    ans += target;
    ans += to_string(count);
    if (ans.size() >= line.size()) {
        cout << line << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}