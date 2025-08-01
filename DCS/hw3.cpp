#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int cal(int );
string decimalToBinary(int );

int main()
{
    ofstream out;
    out.open("out.txt");
    string temp;
    int one,five,ten,total;
    for(int i=1;i<64;i++)
    {
        temp = decimalToBinary(i);
        total = temp[0]*3*4+temp[1]*2*3+temp[2]*3*1 + temp[3]*4*4+temp[4]*2*4+temp[5]*4-48*7*7;

        out<<decimalToBinary(total)[1]<<endl;

    }
    return 0;
}

string decimalToBinary(int decimal) {
    if (decimal == 0)
        return "000000000000";

    std::string binary = "";
    while (decimal > 0) {
        // 取余数作为二进制位
        int remainder = decimal % 2;
        // 将余数转换为字符并插入到字符串的开头
        binary = std::to_string(remainder) + binary;
        // 将十进制数除以2，继续进行下一位的转换
        decimal /= 2;
    }

    // 如果二进制字符串长度不足12位，则在前面补0
    while (binary.length() < 6) {
        binary = "0" + binary;
    }

    return binary;
}
