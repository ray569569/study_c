#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


bool isPalindrome(string s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) {
            return false;
        }
        ++start;
        --end;
    }
    return true;
}

int main() {
    

    string s;
    cin>>s;
  	int start = 0;
  	int end = s.size()-1;
    if(isPalindrome(s, start, end))
        cout<< "True";
    else
        cout<<"False";


    return 0;
}