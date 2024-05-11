#include<iostream>
#include<fstream>
using namespace std;

int main()
{
    ofstream out;
    out.open("out.txt");
    int j=0;
    for(int i=0;i<8;i++)
    {
        out<<i<<":begin"<<endl;
        if(i<4&&i>=0&&(j)<4&&(j)>=0)
            out<<"    total[-2][2]<=total[-2][2] + a_v(in_data,image["<<i<<"]["<<j<<"]);"<<endl;
        
        if((i-1<4)&&(i-1)>=0&&(j)<4&&(j)>=0)
            out<<"    total[-1][2]<=total[-1][2] + a_v(in_data,image["<<i-1<<"]["<<j<<"]);"<<endl;

        if((i-2<4)&&(i-2)>=0&&(j)<4&&(j)>=0)
            out<<"    total[0][2]<=total[0][2] + a_v(in_data,image["<<i-2<<"]["<<j<<"]);"<<endl;
        
        if((i-3<4)&&(i-3)>=0&&(j)<4&&(j)>=0)
            out<<"    total[1][2]<=total[1][2] + a_v(in_data,image["<<i-3<<"]["<<j<<"]);"<<endl;

        if((i-4<4)&&(i-4)>=0&&(j)<4&&(j)>=0)
            out<<"    total[2][2]<=total[2][2] + a_v(in_data,image["<<i-4<<"]["<<j<<"]);"<<endl;
////1

        if(i<4&&i>=0&&(j-1)<4&&(j-1)>=0)
            out<<"    total[-2][1]<=total[-2][1] + a_v(in_data,image["<<i<<"]["<<j-1<<"]);"<<endl;
        
        if((i-1<4)&&(i-1)>=0&&(j-1)<4&&(j-1)>=0)
            out<<"    total[-1][1]<=total[-1][1] + a_v(in_data,image["<<i-1<<"]["<<j-1<<"]);"<<endl;

        if((i-2<4)&&(i-2)>=0&&(j-1)<4&&(j-1)>=0)
            out<<"    total[0][1]<=total[0][1] + a_v(in_data,image["<<i-2<<"]["<<j-1<<"]);"<<endl;
        
        if((i-3<4)&&(i-3)>=0&&(j-1)<4&&(j-1)>=0)
            out<<"    total[1][1]<=total[1][1] + a_v(in_data,image["<<i-3<<"]["<<j-1<<"]);"<<endl;

        if((i-4<4)&&(i-4)>=0&&(j-1)<4&&(j-1)>=0)
            out<<"    total[2][1]<=total[2][1] + a_v(in_data,image["<<i-4<<"]["<<j-1<<"]);"<<endl;
////2  

        if(i<4&&i>=0&&(j-2)<4&&(j-2)>=0)
            out<<"    total[-2][0]<=total[-2][0] + a_v(in_data,image["<<i<<"]["<<j-2<<"]);"<<endl;
        
        if((i-1<4)&&(i-1)>=0&&(j-2)<4&&(j-2)>=0)
            out<<"    total[-1][0]<=total[-1][0] + a_v(in_data,image["<<i-1<<"]["<<j-2<<"]);"<<endl;

        if((i-2<4)&&(i-2)>=0&&(j-2)<4&&(j-2)>=0)
            out<<"    total[0][0]<=total[0][0] + a_v(in_data,image["<<i-2<<"]["<<j-2<<"]);"<<endl;
        
        if((i-3<4)&&(i-3)>=0&&(j-2)<4&&(j-2)>=0)
            out<<"    total[1][0]<=total[1][0] + a_v(in_data,image["<<i-3<<"]["<<j-2<<"]);"<<endl;

        if((i-4<4)&&(i-4)>=0&&(j-2)<4&&(j-2)>=0)
            out<<"    total[2][0]<=total[2][0] + a_v(in_data,image["<<i-4<<"]["<<j-2<<"]);"<<endl;
////3
        
        if(i<4&&i>=0&&(j-3)<4&&(j-3)>=0)
            out<<"    total[-2][-1]<=total[-2][-1] + a_v(in_data,image["<<i<<"]["<<j-3<<"]);"<<endl;
        
        if((i-1<4)&&(i-1)>=0&&(j-3)<4&&(j-3)>=0)
            out<<"    total[-1][-1]<=total[-1][-1] + a_v(in_data,image["<<i-1<<"]["<<j-3<<"]);"<<endl;

        if((i-2<4)&&(i-2)>=0&&(j-3)<4&&(j-3)>=0)
            out<<"    total[0][-1]<=total[0][-1] + a_v(in_data,image["<<i-2<<"]["<<j-3<<"]);"<<endl;
        
        if((i-3<4)&&(i-3)>=0&&(j-3)<4&&(j-3)>=0)
            out<<"    total[1][-1]<=total[1][-1] + a_v(in_data,image["<<i-3<<"]["<<j-3<<"]);"<<endl;

        if((i-4<4)&&(i-4)>=0&&(j-3)<4&&(j-3)>=0)
            out<<"    total[2][-1]<=total[2][-1] + a_v(in_data,image["<<i-4<<"]["<<j-3<<"]);"<<endl;
////4

        if(i<4&&i>=0&&(j-4)<4&&(j-4)>=0)
            out<<"    total[-2][-2]<=total[-2][-2] + a_v(in_data,image["<<i<<"]["<<j-4<<"]);"<<endl;
        
        if((i-1<4)&&(i-1)>=0&&(j-4)<4&&(j-4)>=0)
            out<<"    total[-1][-2]<=total[-1][-2] + a_v(in_data,image["<<i-1<<"]["<<j-4<<"]);"<<endl;

        if((i-2<4)&&(i-2)>=0&&(j-4)<4&&(j-4)>=0)
            out<<"    total[0][-2]<=total[0][-2] + a_v(in_data,image["<<i-2<<"]["<<j-4<<"]);"<<endl;
        
        if((i-3<4)&&(i-3)>=0&&(j-4)<4&&(j-4)>=0)
            out<<"    total[1][-2]<=total[1][-2] + a_v(in_data,image["<<i-3<<"]["<<j-4<<"]);"<<endl;

        if((i-4<4)&&(i-4)>=0&&(j-4)<4&&(j-4)>=0)
            out<<"    total[2][-2]<=total[2][-2] + a_v(in_data,image["<<i-4<<"]["<<j-4<<"]);"<<endl;

        out<<"end"<<endl;
    }
    return 0;
}