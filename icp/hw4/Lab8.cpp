#include <iomanip>
#include <iostream>
using namespace std;

void getJudgeData(double &score) {
    cout << "Enter a judge's score: ";
    cin >> score;
    while (score < 0 || score > 10) {
        cout << "Invalid score. Enter a score between 0 and 10: ";
        cin >> score;
    }
}

int findLowest(double scores[]) {
    int lowest = 0;
    for (int i = 1; i < 5; i++) {
        if (scores[i] < scores[lowest]) {
            lowest = i;
        }
    }
    return lowest;
}

int findHighest(double scores[]) {
    int highest = 0;
    for (int i = 1; i < 5; i++) {
        if (scores[i] > scores[highest]) {
            highest = i;
        }
    }
    return highest;
}

double calcScore(double scores[]) {
    double total = 0;
    for (int i = 0; i < 5; i++) {
        total += scores[i];
    }
    int lowest = findLowest(scores);
    int highest = findHighest(scores);
    total -= scores[lowest];
    total -= scores[highest];
    return total / 3;
}

int main() {
    double scores[5];
    for (int i = 0; i < 5; i++) {
        getJudgeData(scores[i]);
    }
    cout << "Contestant's score: " << calcScore(scores) << endl;
    return 0;
}