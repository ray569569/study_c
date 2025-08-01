#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream in("./lab4/t8.txt");
    string line;
    in >> line;
    int Max = 0;
    vector<char> ans;
    for (int i = 0; i < line.size(); i++) {
        for (int j = i; j < line.size(); j++) {
            for (int k = 0; k < ans.size(); k++) {
                if (ans[k] == line[j]) {
                    goto next;
                }
            }
            ans.push_back(line[j]);
        }
    next:
        Max = max(Max, (int)ans.size());
        ans.clear();
    }
    cout << Max << endl;
    return 0;
}