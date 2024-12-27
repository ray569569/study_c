#include<iostream>
using namespace std;

int main()
{
    for(int i=0;i<1000;i++)
    {
        int num = i;
        int sum = 0;
        int sqr = i*i;
        int sqr_sum = 0;
        int cube = i*i*i;
        int cube_sum = 0;
        while(num>0)
        {
            sum = sum + num%10;
            num = num/10;
        }
        while(sqr>0)
        {
            sqr_sum = sqr_sum + sqr%10;
            sqr = sqr/10;
        }
        while(cube>0)
        {
            cube_sum = cube_sum + cube%10;
            cube = cube/10;
        }
        if(sqr_sum == sum && cube_sum == sum)
        {
            cout<<i<<endl;
        }
    }
    return 0;
}