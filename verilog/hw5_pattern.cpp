#include <iostream>
#include <random>
#include <bitset>
#include <iomanip>
#include<fstream>
using namespace std;


int main() {
    // 使用隨機數引擎和分佈來生成隨機數
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(1, 50); // 數字的範圍是從 1 到 50
    uniform_int_distribution<int> dis_binary(0, 31);
    vector<int> numbers;
    string opcode;
    string rs_add;
    string rt_add;
    string rd_add;
    string shamt;
    string funct;
    string immediate;
    string preout;
    bool flag;
    long long r0 = 0,r1=0,r2=0,r3=0,r4=0,r5=0;
    int fail=0;
    const int num_numbers_per_set = 6;
    // 生成 5000 筆隨機數
    const int num_random_numbers = 10000;
    ofstream out;
    ofstream in;
    in.open("input.txt");
    out.open("output.txt");
    int count =0;

    while(count<200000){
        unsigned int random_number = dis(gen);
        // 將數字轉換為32位的二進制字串

        numbers.clear();
        for (int j = 0; j < num_numbers_per_set; ++j) {
            int random_number = dis(gen);
            numbers.push_back(random_number);
            //cout << random_number << " ";
        }

        switch(numbers[0]%3)
        {
            case 0:opcode = "000000";
                break;
            case 1:opcode = "001000";
                break;
            case 2:opcode = "100000";
                break;
        }
        switch(numbers[1]%6)
        {
            case 0:rs_add = "10001";
                break;
            case 1:rs_add = "10010";
                break;
            case 2:rs_add = "01000";
                break;
            case 3:rs_add = "10111";
                break;
            case 4:rs_add = "11111";
                break;
            case 5:rs_add = "10000";
                break;
        }
        switch(numbers[2]%6)
        {
            case 0:rt_add = "10001";
                break;
            case 1:rt_add = "10010";
                break;
            case 2:rt_add = "01000";
                break;
            case 3:rt_add = "10111";
                break;
            case 4:rt_add = "11111";
                break;
            case 5:rt_add = "10000";
                break;
        }
        switch(numbers[3]%6)
        {
            case 0:rd_add = "10001";
                break;
            case 1:rd_add = "10010";
                break;
            case 2:rd_add = "01000";
                break;
            case 3:rd_add = "10111";
                break;
            case 4:rd_add = "11111";
                break;
            case 5:rd_add = "10000";
                break;
        }
        switch(numbers[4]%6)
        {
            case 0:funct = "100000";
                break;
            case 1:funct = "100100";
                break;
            case 2:funct = "100101";
                break;
            case 3:funct = "100111";
                break;
            case 4:funct = "000000";
                break;
            case 5:funct = "000010";
                break;
        }
        
        int random_binary = dis_binary(gen);
        bitset<5> binary(random_binary);
        shamt = binary.to_string();
        fail = 0;
        int rs,rt,result;
        immediate = rd_add + shamt + funct;
        //in<<opcode<<endl<<rs_add<<endl<<rt_add<<endl<<immediate<<endl;
        
        if(rs_add == preout||rt_add == preout)
        {
            flag = 0;
        }
        else
            flag = 1;
        if(flag)
        {
        in<<(opcode+rs_add+rt_add+immediate)<<endl;
        if(rs_add == "10001")
            rs = r0;
        if(rs_add == "10010")
            rs = r1;
        if(rs_add == "01000")
            rs = r2;
        if(rs_add == "10111")
            rs = r3;
        if(rs_add == "11111")
            rs = r4;
        if(rs_add == "10000")
            rs = r5;

        if(rt_add == "10001")
            rt = r0;
        if(rt_add == "10010")
            rt = r1;
        if(rt_add == "01000")
            rt = r2;
        if(rt_add == "10111")
            rt = r3;
        if(rt_add == "11111")
            rt = r4;
        if(rt_add == "10000")
            rt = r5;




        if(opcode == "000000")
        {
            if(funct == "100000")
            {
                result = rs+ rt;
            }
            else if(funct == "100100")
            {
                result = rs&rt;
            }
            else if(funct == "100101")
            {
                result = rs|rt;
            }
            else if(funct == "100111")
            {
                result = ~(rs|rt);
            }
            else if(funct == "000000")
            {
                result = rt<<stoi(shamt, nullptr, 2);
            }
            else if(funct == "000010")
            {
                result = rt>>stoi(shamt, nullptr, 2);
            }
            
            if(rd_add == "10001")
                r0 = result;
            if(rd_add == "10010")
                r1 = result;
            if(rd_add == "01000")
                r2 = result;
            if(rd_add == "10111")
                r3 = result;
            if(rd_add == "11111")
                r4 = result;
            if(rd_add == "10000")
                r5 = result;
            preout = rd_add;
        }
        else if(opcode == "001000")
        {
            result = rs + stoi(immediate, nullptr, 2);
            if(rt_add == "10001")
                r0 = result;
            if(rt_add == "10010")
                r1 = result;
            if(rt_add == "01000")
                r2 = result;
            if(rt_add == "10111")
                r3 = result;
            if(rt_add == "11111")
                r4 = result;
            if(rt_add == "10000")
                r5 = result;
            preout = rt_add;
        }
        else
        {
            preout = "";
            fail =1;
        }
        while(r0<0)
            r0 +=65536;
        while(r0>=65536)
            r0 -=65536;
        while(r1<0)
            r1 +=65536;
        while(r1>=65536)
            r1 -=65536;
        while(r2<0)
            r2 +=65536;
        while(r2>=65536)
            r2 -=65536;
        while(r3<0)
            r3 +=65536;
        while(r3>=65536)
            r3 -=65536;
        while(r4<0)
            r4 +=65536;
        while(r4>=65536)
            r4 -=65536;
        while(r5<0)
            r5 +=65536;
        while(r5>=65536)
            r5 -=65536;
        out<<fail<<setw(25)<<r0<<setw(25)<<r1<<setw(25)<<r2<<setw(25)<<r3<<setw(25)<<r4<<setw(25)<<r5<<endl;
        count++;
        }
        


    }

    return 0;
}
