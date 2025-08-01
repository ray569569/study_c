#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Student {
   private:
    string name;
    double average;
    vector<int> scores;

   public:
    void setName(const string& studentName) {
        name = studentName;
    }

    void addScore(int score) {
        // To do list
        scores.push_back(score);
        // end of To do lists
    }
    void addAvg(double score) {
        // To do list
        average = score;
        // end of To do lists
    }

    double getAverage() const {
        // To do list
        double avg = 0;
        for (int i = 0; i < scores.size(); i++) {
            avg += scores[i];
        }
        double num = scores.size();
        avg /= num;
        return avg;
        // end of To do lists
    }

    void displayInfo() const {
        // To do list
        cout << "student name: " << name << endl;
        cout << "all score: ";
        for (int i = 0; i < scores.size(); i++) {
            cout << scores[i] << " ";
        }
        cout << endl;
        cout << "average score: " << average;

        // end of To do lists
    }
};

int main() {
    ifstream file("./Q2/Q2_T10.txt");
    if (!file) {
        cout << "Error: Could not open file example.txt" << endl;
        return 1;
    }

    Student student;
    string line;
    // To do list
    file >> line;
    student.setName(line);
    while (1) {
        file >> line;
        if (line != "-1") {
            student.addScore(stoi(line));
        } else
            break;
    }
    student.addAvg(student.getAverage());
    // end of To do lists
    file.close();
    student.displayInfo();

    return 0;
}
