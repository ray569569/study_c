#include <iostream>
#include <string>
using namespace std;

class Time24
{
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time24(int h = 0, int m = 0, int s = 0)
    {
        if (h >= 0 && h <= 23)
            hours = h;
        else
            hours = 0;
        if (m >= 0 && m <= 59)
            minutes = m;
        else
            minutes = 0;
        if (s >= 0 && s <= 59)
            seconds = s;
        else
            seconds = 0;
    }
    void display24()
    {
        cout <<"Time in 24-hours notation->"<< hours << ":" << minutes << ":" << seconds << endl;
    }
    void display12()
    {
        if (hours > 12)
            cout <<"Time in 12-hours notation->" << hours - 12 << ":" << minutes << ":" << seconds << " pm" << endl;
        else
            cout <<"Time in 12-hours notation->" << hours << ":" << minutes << ":" << seconds << " am" << endl;
    }
    void displayGreeting()
    {
        if (hours >= 6 && hours <= 11)
            cout << "Good Morning!!" << endl;
        else if (hours >= 12 && hours <= 17)
            cout << "Good Afternoon!!" << endl;
        else if (hours >= 18 && hours <= 22)
            cout << "Good Evening!!" << endl;
        else
            cout << "Time to Sleep!!" << endl;
    }
};

int main()
{
    cout<<"Hours:";
    int h;
    cin>>h;
    cout<<"Minutes:";
    int m;
    cin>>m;
    cout<<"Seconds:";
    int s;
    cin>>s;
    Time24 t1(h, m, s);
    t1.display24();
    t1.display12();
    t1.displayGreeting();
    return 0;
}
