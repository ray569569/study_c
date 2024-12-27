#include <iostream>
using namespace std;

int main() {
    int score = -1;
    cout << "Enter total score (0-500): ";
    cin >> score;

    if (score < 0 || score > 500) 
        cout << "Invalid score!" << endl;
    else if (score >= 400) 
        cout << "A" << endl;
    else if (score >= 300) 
        cout << "B" << endl;
    else if (score >= 200) 
        cout << "C" << endl;
    else 
        cout << "D" << endl;
    return 0;
}
