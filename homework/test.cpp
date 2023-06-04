#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

class weekday
{
private:
    int day;
    int month;
    int year;
    int week;
    int cen;
    int calmonth;
    int calyear;
    void getInput(int a,int b,int c);
    bool isLeapYear();
    void getCenturyValue();
    void getYearValue();
    void getMonthValue();
public:
    void getweekday(int a,int b,int c);
};
void weekday::getInput(int a,int b,int c)
{
    day = b;
    month=a;
    year = c;
}
bool weekday::isLeapYear()
{
    if((year%400==0)||((year%4==0)&&(year%100 !=0)))
    return 1;
    else
    return 0;
}
void weekday::getCenturyValue()
{
    int t = year/100;
    cen = (3-t%4)*2;
}
void weekday::getYearValue()
{
    int t= year%100;
    int k=t;
    calyear = t+k/4;
}
void weekday::getMonthValue()
{
    if(isLeapYear()==1)
    {
        int array[12]={6,2,3,6,1,4,6,2,5,0,3,5};
        calmonth= array[month-1]; 
    }
    else
    {
        int array[12]={0,3,3,6,1,4,6,2,5,0,3,5};
        calmonth= array[month-1]; 
    }
}
void weekday::getweekday(int a,int b,int c)
{
    getInput(a,b,c);
    getMonthValue();
    getYearValue();
    getCenturyValue();
    string A[7] = {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    cout<<day<<endl<<calmonth<<endl<<calyear<<endl<<cen<<endl;
    int key = (cen+day+calmonth+calyear)%7;
    cout<<A[key]<<endl;
}

int main()
{
    weekday B;
    ifstream in;
    in.open("input.txt");
    string a;
    int b,c;
    
    in>>a>>b>>c;
    if(a.size()==1)
    {
        stringstream ss1;
        ss1<<a;
        int k;
        ss1>>k;
        B.getweekday(k,b,c);
    }
    else
    {
        int q=0;
        string array[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
        for(int i=0;i<12;i++)
        {
            if(a == array[i])
            q=i+1;
        }
        B.getweekday(q,b,c);
    }
    
    return 0;
}