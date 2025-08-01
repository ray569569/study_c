#include <iostream>
using namespace std;

int main() {
    int hour, min, sec;
    hour = 2;
    min = 20;
    sec = 12;
    cout << hour * 60 * 60 + min * 60 + sec << endl;
    return 0;
}