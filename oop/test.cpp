#include<iostream>
using namespace std;

class circle{
public:
    int radius;
    int length;
    float area;
    float getarea()
    {
        return radius*radius*3.14;
    }
    int compare(int radius1)
    {
        if(radius>radius1)
        return -1;
        else if(radius<radius1)
        return 1;
        else 
        return 0;

    }
};

int main()
{
    /*
    circle a;
    a.radius = 10;
    cout<< a.getarea()<<endl;
    return 0;
    */

   circle b,c;
   b.radius = 10;
   c.radius = 10;
   cout<<c.compare(b.radius)<<endl;
   return 0;
   
}