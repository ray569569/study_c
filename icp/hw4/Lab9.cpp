#include <iomanip>
#include <iostream>
using namespace std;

void getScore(double &score) {
    cout << "Enter test score: ";
    cin >> score;
    while (score < 0 || score > 100) {
        cout << "Invalid test score. Enter a score between 0 and 100: ";
        cin >> score;
    }
}

int findLowest(double scores[], int size) {
    int lowestIndex = 0;
    for (int i = 1; i < size; i++) {
        if (scores[i] < scores[lowestIndex]) {
            lowestIndex = i;
        }
    }
    return lowestIndex;
}

void calcAverage(double scores[], int size) {
    int lowestIndex = findLowest(scores, size);
    double total = 0;
    for (int i = 0; i < size; i++) {
        if (i != lowestIndex) {
            total += scores[i];
        }
    }
    cout << "Average of the four highest scores: " << fixed << setprecision(2) << total / (size - 1) << endl;
}

int main() {
    const int numScores = 5;
    double scores[numScores];
    for (int i = 0; i < numScores; i++) {
        getScore(scores[i]);
    }
    calcAverage(scores, numScores);
    return 0;
}