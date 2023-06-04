#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class Point
{
private:
    int x;
    int y;
public:
    Point(int a,int b)
    {
        x=a,y=b;
    }
    int getX()
    {
        return x;
    }
    int getY()
    {
        return y;
    }
};

class Polygon
{
private:
    vector<Point> points;
public:
    Polygon(char *filename)
    {
        ifstream in;
        in.open("case2.txt");
        while(!in.eof())
        {
            int c,d;
            in>>c>>d;
            Point temp(c,d);
            points.push_back(temp);
        }
        points.push_back(points[0]);
    }
    double calcArea()
    {
        int sum1=0;
        int sum2=0;
        int sum3=0;
        int size = points.size();
        for(int i=0;i<size-1;i++)
        {
            sum1 += points[i].getX()*points[i+1].getY();
            sum2 += points[i+1].getX()*points[i].getY(); 
        }
        sum3 = sum1-sum2;
        if(sum3<0)
        {
            sum3 = -sum3;
        }
        return 
            1.0*sum3/2;
    }
};
int main(int argc,char* argv[])
{
    Polygon p(argv[1]);
    cout<<p.calcArea()<<endl;
    return 0;
}