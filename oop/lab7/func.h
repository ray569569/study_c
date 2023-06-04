#include<iostream>
using namespace std;

class PolySeq
{
public:
    PolySeq(int* ,int);
    PolySeq();
    PolySeq Add(PolySeq);
    PolySeq Derivative();
    int integral(int,int);
    int* coef;
    int num;
};

namespace Poly_int
{
    int getvalue(PolySeq,int);
}
namespace Poly_float
{
    float getvalue(PolySeq, float);
}