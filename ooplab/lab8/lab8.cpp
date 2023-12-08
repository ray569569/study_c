#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

class Pet
{
protected:
    string name;
    int weight;
    int lifespan =12;
public:
    string getname()
    {
        return name;
    }
};
class dog:public Pet
{
private:
    string breed;
    string type;
public:
    dog(string t,int w,string n)
    {
        type = t;
        weight = w;
        name =n;
    }
    void setweight()
    {   
        if(type=="husky"&&weight>50)
        {
            lifespan -=2;
        }
        else if(type=="husky"&&weight<=50)
        {
            lifespan +=3;
        }
        else if(type=="corgi"&&weight>30)
        {
            lifespan +=1;
        }
        else if(type=="corgi"&&weight<=30)
        {
            lifespan +=1;
        }
    }
    string getbreed()
    {
        return breed;
    }
    string gettype()
    {
        return type;
    }
    int getlife()
    {
        return lifespan;
    }
};
class cat:public Pet
{
private:
    string color;
    int cute;
public:
    cat(string col,int w,string n)
    {
        color = col;
        weight =w;
        name =n;
    }
    void setweight()
    {   
        if(weight>20)
        {
            lifespan-=2;
        }
        else if(weight<=20)
        {
            lifespan+=3;
        }
    }
    void setcute()
    {
        if(color=="orange")
        {
            cute = 100-weight;
        }
        else if(color=="tabby")
        {
            cute = 90-weight;
        }
        else 
        {
            cute = 70-weight;
        }
    }
    int getcute()
    {
        return cute;
    }
    int getlife()
    {
        return lifespan;
    }
    string gettype()
    {
        return color;
    }
};
int main()
{
    ifstream in;
    in.open("input1.txt");
    int n;
    in>>n;

    string* petname ;
    int* wei;
    string* cha;
    petname = new string[n];
    wei = new int[n];
    cha = new string[n];
    for(int i =0;i<n;i++)
    {
        in>>petname[i]>>wei[i]>>cha[i];
    }

    vector<dog> d;
    vector<cat> c;

    for(int i=0;i<n;i++)
    {
        if(cha[i] == "husky")
        {
            dog t("husky",wei[i],petname[i]);
            t.setweight();
            d.push_back(t);
        }
        else if(cha[i] == "corgi")
        {
            dog t("corgi",wei[i],petname[i]);
            t.setweight();
            d.push_back(t);
        }
        else if(cha[i] == "orange")
        {
            cat t("orange",wei[i],petname[i]);
            t.setweight();
            t.setcute();
            c.push_back(t);
        }
        else if(cha[i] == "orange")
        {
            cat t("tabby",wei[i],petname[i]);
            t.setweight();
            t.setcute();
            c.push_back(t);
        }
        else 
        {
            cat t(cha[i],wei[i],petname[i]);
            t.setweight();
            t.setcute();
            c.push_back(t);
        }
    }
    for(int i=0;i<d.size();i++)
    {
        cout<<d[i].getname()<<" "<<d[i].gettype()<<" "<<d[i].getlife()<<endl;
    }
    cout<<endl;
    for(int i=0;i<c.size();i++)
    {
        cout<<c[i].getname()<<" "<<c[i].gettype()<<" "<<c[i].getlife()<<" "<<c[i].getcute()<<endl;
    }
    return 0;
}