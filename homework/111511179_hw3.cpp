#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

string* addEntry(string* dynemicArray, int &size, string newentry);
string* deleteEntry(string* dynemicArray, int &size, string entrytodelete, ofstream &outf);

int main()
{
    ifstream in;
    ofstream out;

    in.open("case5.txt");
    out.open("Output1.txt");

    int num;
    int size =0;
    int sum =0;
    string *ptr ;
    ptr = new string[size];
    
    in >>num;

    for(int i=0;i<num+2;i++)
    {
        string temp;
        string code;
        stringstream ss1;
        getline(in,temp);
        ss1 <<temp;
        temp = "";

        ss1>>temp;
        if(temp == "add")
        {
            ss1 >>code;
            ptr = addEntry(ptr,size,code);
        }
        else if(temp == "delete")
        {
            ss1>>code;
            ptr = deleteEntry(ptr,size,code,out);
        }
    }
    
    out<<endl<<size<<endl;
    for(int i=0;i<size;i++)
    {
        out<<*(ptr+i)<<endl;
    }
    in.close();
    out.close();
    return 0;
}

string* addEntry(string* dynemicArray, int &size, string newentry)
{
    size++;
    string* p1 = new string[size];
    
    for(int i=0;i<size-1;i++)
    {
        *(p1+i) = *(dynemicArray+i);
    }
    *(p1+size-1) = newentry;
    return p1;
}

string* deleteEntry(string* dynemicArray, int &size, string entrytodelete, ofstream &outf)
{
    bool find = false;
    for(int i=0;i<size;i++)
    {
        if(*(dynemicArray+i) == entrytodelete)
        {
            find = true;
        }
        else
        ;
    }

    if(find == true)
    {
        int con=0;
        size--;
        string* p2;
        bool button = true;
        p2 = new string[size];

        for(int i=0;i<size+1;i++)
        {
            if((*(dynemicArray+i) == entrytodelete) && (button ==true))
            {
                button = false;
                con =1;
                continue;
            }
            else 
            {
                *(p2+i-con) = *(dynemicArray+i);
            }

        }
        return p2;
    }
    else
    {
        outf << "null" <<endl;
        return dynemicArray;
    }
}

