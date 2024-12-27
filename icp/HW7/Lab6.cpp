#include <iostream>
#include <string>
using namespace std;

class StudentPerformance
{
private:
    string name;
    int academicScore;
    int extraCurricularScore;

public:
    StudentPerformance()
    {
        name = "";
        academicScore = 0;
        extraCurricularScore = 0;
    }
    string getName()
    {
        return name;
    }
    int getAcademicScore()
    {
        return academicScore;
    }
    int getExtraCurricularScore()
    {
        return extraCurricularScore;
    }
    int getPerformance()
    {
        return 0.75 * academicScore + 0.25 * extraCurricularScore;
    }
    char getGrade()
    {
        int performance = getPerformance();
        if (performance >= 80)
            return 'A';
        else if (performance >= 65)
            return 'B';
        else if (performance >= 50)
            return 'C';
        else
            return 'D';
    }
    void setName(string n)
    {
        name = n;
    }
    void setAcademicScore(int a)
    {
        academicScore = a;
    }
    void setExtraCurricularScore(int e)
    {
        extraCurricularScore = e;
    }
};

int main()
{
    StudentPerformance s1;
    string name;
    int academicScore, extraCurricularScore;
    cout << "Enter name of the student : ";
    getline(cin, name);
    s1.setName(name);
    cout << "Enter academic score ( 0 - 100): ";
    cin >> academicScore;
    s1.setAcademicScore(academicScore);
    cout << "Enter extra curricular score ( 0 - 100): ";
    cin >> extraCurricularScore;
    s1.setExtraCurricularScore(extraCurricularScore);
    cout << "Performance Score : " << s1.getPerformance() << endl;
    cout << "Grade awarded : " << s1.getGrade() << endl;
    return 0;
}