#include<iostream>
#include<fstream>
#include <iomanip>
using namespace std;

struct student
{
    int quiz1;
    int quiz2;
    int midterm;
    int final;
    double average;
    char grade;
};
double calculate(double a,double b,double c,double d);
char gra(double a);
int main(int argc,char *argv[])
{
    ifstream in;
    in.open("input.txt");
    
    student a;
    in>>a.quiz1>>a.quiz2>>a.midterm>>a.final;
    a.average = calculate(a.quiz1,a.quiz2,a.midterm,a.final);
    cout<<"Quiz 1: "<<a.quiz1<<endl<<"Quiz 2: "<<a.quiz2<<endl<<"Midterm: "<<a.midterm<<endl<<"Final: "<<a.final<<endl<<"Average numeric score: "<<setw(2)<<a.average<<endl<<"Final letter grade: "<<gra(a.average)<<endl;
    in.close();
    return 0;
}

double calculate(double a,double b,double c,double d)
{
    double k;
    k=((a*10.0+b*10.0)*0.125+c*0.25+d*0.5);
    return k;
}

char gra(double a)
{
    switch(int(a/10))
    {
        case 10:
        case 9:
        return 'A';
        case 8:
        return 'B';
        case 7:
        return 'C';
        case 6:
        return 'D';
        default:
        return 'F';
    }
}