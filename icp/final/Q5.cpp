#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isPalindrome(const string& s, int start, int end);
void Partition(string s, int start, vector<string>& current, vector<vector<string>>& result);

void Partition(string s, int start, vector<string>& current, vector<vector<string>>& result) {
    if (start == s.size()) {
        result.push_back(current);
        return;
    }
    for (int end = start; end < s.size(); ++end) {
        if (isPalindrome(s, start, end)) {
            current.push_back(s.substr(start, end - start + 1));
            Partition(s, end + 1, current, result);
            current.pop_back();
        }
    }
}

bool isPalindrome(const string& s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        ++start;
        --end;
    }
    return true;
}

int Count(string s) {
    vector<vector<string>> result;
    vector<string> current;
    Partition(s, 0, current, result);
    return result.size();
}

int main() {
    ifstream file("./Q5/Q5_T10.txt");
    if (!file) {
        cerr << "Error: Could not open file example.txt" << endl;
        return 1;
    }

    string s;
    getline(file, s);
    int sum = Count(s);
    cout << sum;
    file.close();

    return 0;
}