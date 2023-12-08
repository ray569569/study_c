#include<iostream>
#include<iomanip>
#include<fstream>
using namespace std;

class student
{
private:
    int quiz1;
    int quiz2;
    int midterm;
    int final;
    double average;
    char grade;
public:
    void setgrade(int a,int b,int c,int d);
    void calculate();
    void getgrade();
    void printgrade();
};

void student::setgrade(int a,int b,int c,int d)
{
    quiz1 = a;
    quiz2 = b;
    midterm = c;
    final = d;
    return 
    ;
}
void student::calculate()
{
    average = ((double(quiz1)*10+double(quiz2)*10)*0.125+double(midterm)*0.25+double(final)*0.5);
}
void student::getgrade()
{
    switch(int(average/10))
    {
        case 10:
        case 9:
        grade = 'A';
        break;
        case 8:
        grade = 'B';
        break;
        case 7:
        grade = 'C';
        break;
        case 6:
        grade = 'D';
        break;
        default:
        grade = 'F';
    }
    return 
    ;
}
void student::printgrade()
{
    cout<<"Quiz 1: "<<quiz1<<endl<<"Quiz 2: "<<quiz2<<endl<<"Midterm: "<<midterm<<endl<<"Final: "<<final<<endl<<"Average numeric score: "<<setw(2)<<average<<endl<<"Final letter grade: "<<grade;
}
int main(int argc,char *argv[])
{
    student a;
    ifstream in;
    in.open("input.txt");

    int b,c,d,e;
    in>>b>>c>>d>>e;
    a.setgrade(b,c,d,e);
    a.calculate();
    a.getgrade();
    a.printgrade();
    return 0;
}

