#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class Person
{
private:
    int num;
    string* name;
public:
    Person()
    {
        num =0;
        name = new string[num];
    }
    Person(int a)
    {
        num =a;
        name = new string[num];
    }
    Person(int a,string* b)
    {
        num =a;
        name = new string[num];
        for(int i=0;i<num;i++)
        {
            name[i] = b[i];
        }
    }
    void setperson(int a,string* b)
    {
        num =a;
        name = new string[num];
        for(int i=0;i<num;i++)
        {
            name[i] = b[i];
        }
    }
    string getperson(int a)
    {
        return name[a];
    }
    int getpersonnum()
    {
        return num;
    }
};

class Patient:public Person
{
private:
    int pat;
    string* spec;
public:
    Patient()
    {
        pat =0;
        spec = new string[pat];
    }
    Patient(int a)
    {
        pat =a;
        spec = new string[pat];    
    }
    Patient(int a,string* b)
    {
        pat = a;
        spec = new string[pat];
        for(int i=0;i<pat;i++)
        {
            spec[i]=b[i];
        }
    }
    string getspec(int a)
    {
        return spec[a];
    }
};

class Doctor:public Person
{
private:
    int doc;
    string* docspec;
    double* fee;
public:
    Doctor()
    {
        doc =0;
        docspec = new string[doc];
        fee = new double[doc];
    }
    Doctor(int a)
    {
        doc =a;
        docspec = new string[doc];  
        fee = new double[doc];  
    }
    Doctor(int a,string* b,double* c)
    {
        doc = a;
        docspec = new string[doc];
        fee = new double[doc];
        for(int i=0;i<doc;i++)
        {
            docspec[i]=b[i];
        }
        for(int i=0;i<doc;i++)
        {
            fee[i]=c[i];
        }
    }   
    string getdocspec(int a)
    {
        return docspec[a];
    }
    double getfee(int i)
    {
        return fee[i];
    }
    int choosedocfee(string a)
    {
        for(int i=0;i<doc;i++)
        {
            if(a == docspec[i])
            {
                return i;
            }
        }
        return 0;
    }
    int choosedoc(string a)
    {
        for(int i=0;i<doc;i++)
        {
            if(a == docspec[i])
            {
                return i;
            }
            else
            ;
        }
        return 0;
    }
};

class Bill
{
private:
    Doctor a;
    Patient b;
    double* c;
public:
    Bill(Doctor x,Patient y,double* z,int n)
    {
        a=x;
        b=y;
        c = new double[n];
        for(int i=0;i<n;i++)
        {
            c[i] = z[i];
        }
    }
    double getbill(int i)
    {
        return c[i];
    }

};

int main(int argc,char* argv[])
{

    ifstream in;
    in.open(argv[1]);
    int n;
    string* s;
    in>>n;
    s = new string[n];
    for(int i=0;i<n;i++)
    {
        in>>s[i];
    }
    Person p(n,s);

    int n1;
    string* s1;
    in>>n1;
    s1 = new string[n1];
    string* patspec;
    patspec = new string[n1];
    for(int i=0;i<n1;i++)
    {
        in>>s1[i]>>patspec[i];
    }
    Patient p1(n1,patspec);
    p1.setperson(n1,s1);

    int n2;
    string* s2;
    in>>n2;
    s2 = new string[n2];
    string* docspec;
    docspec = new string[n2];
    double* bil;
    bil = new double[n2];
    for(int i=0;i<n2;i++)
    {
        in>>s2[i]>>docspec[i]>>bil[i];
    }
    Doctor p2(n2,docspec,bil);
    p2.setperson(n2,s2);    
    
    Bill f(p2,p1,bil,n2);

    for(int i=0;i<p1.getpersonnum();i++)
    {
        cout<<"Bill"<<i+1<<": "<<p1.getperson(i)<<" "<<p2.getperson(p2.choosedocfee(p1.getspec(i)))<<" "<<f.getbill(p2.choosedocfee(p1.getspec(i)))<<endl;
    }
    in.close();
    return 0;
}