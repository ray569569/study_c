#include<iostream>
#include<string>
using namespace std;

int cal_carry(char d1, char d2, int ci)
{
    int do1,do2;
    if(d1>'9')
        do1 = d1 - 'a'+10;
    else
        do1 = d1 - '0';
    if(d2>'9')
        do2 = d2 - 'a'+10;
    else
        do2 = d2 - '0';
    return (do1+do2+ci)>16;
}

char cal_sum(char d1, char d2, int ci)
{
    int do1,do2;
    int so;
    if(d1>'9')
        do1 = d1 - 'a'+10;
    else
        do1 = d1 - '0';
    if(d2>'9')
        do2 = d2 - 'a'+10;
    else
        do2 = d2 - '0';
    so = (do1+do2+ci)%16;
    if(so > 9)
        return so-10+'a';
    else
        return so + '0';
}

int main()
{
    while(1)
    {
        string num1, num2;
        cout<<"Enter two numbers"<<endl;
        cin>>num1>>num2;
        int n1 = num1.length();
        int n2 = num2.length();
        char num1_arr[n1],num2_arr[n2];
        for(int i=0;i<num1.length();i++)
        {
            
            num1_arr[n1 -1-i] = num1[i];
        }
        for(int i=0;i<num2.length();i++)
        {
            num2_arr[n2-1-i] = num2[i];
        }
        
        int count = 0;
        int carry = 0;
        string result = "";
        char new_dig;

        while(count<=num1.length() || count<=num2.length())
        {
            char n1_dig,n2_dig;
            if(count>=num2.length())
                n2_dig = '0';
            else
                n2_dig = num2_arr[count];
            if(count>=num1.length())
                n1_dig = '0';
            else
                n1_dig = num1_arr[count];

            new_dig = cal_sum(n1_dig,n2_dig,carry);
            carry = cal_carry(n1_dig,n2_dig,carry);
            result = new_dig + result;
            count++;
        }
        if(result[0]=='0')
            result = result.substr(1);
        cout<<result<<endl;
        cout<<"Do you want to continue? (Y/N)"<<endl;
        char c;
        cin>>c;
        if(c=='N')
            break;
        
    }
    return 0;
}