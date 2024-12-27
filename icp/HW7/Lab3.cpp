#include <iostream>
#include <cmath>
using namespace std;

class IsoscelesTriangle
{
private:
    int base;
    int height;

public:
    IsoscelesTriangle(int b = 0, int h = 0)
    {
        base = b;
        height = h;
    }
    int area()
    {
        return 0.5 * base * height;
    }
    int perimeter()
    {
        double side = sqrt((base / 2.0) * (base / 2.0) + height * height);
        return base + 2 * side;
    }
};

int main()
{
    int b, h;
    cout << "Enter base of triangle :";
    cin >> b;
    cout << "Enter height of triangle :";
    cin >> h;
    IsoscelesTriangle t1(b, h);
    cout << "Area = " << t1.area() << endl;
    cout << "Perimeter = " << t1.perimeter() << endl;
    return 0;
}