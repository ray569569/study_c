#include<iostream>
#include<fstream>
using namespace std;

class Vector
{
private:
    string* arr;
    int len;
public:
    void operator =(Vector a)
    {
        for(int i=0;i<len;i++)
        {
            arr[i] = a.arr[i];
        }
    }
    void addp(Vector h)
    {
        len++;
        arr=new string[len];
        for(int i=0;i<h.len;i++)
        {
            arr[i] = h.arr[i];
        }
    }
    void decp(Vector h)
    {
        if(h.len == len)
        {
            for(int i=0;i<h.len;i++)
            {
                arr[i] = h.arr[i];
            }
        }
        else 
        {
            len--;
            arr = new string[len];
            for(int i=0;i<h.len;i++)
            {
                arr[i] = h.arr[i];
            }
        }
    }
    void printfuc(ofstream &out)
    {
        out<<len<<endl;
        for(int i=0;i<len;i++)
        {
            out<<arr[i]<<endl;
        }
    }
    Vector()
    {
        len =0;
        arr = new string[len];
    }
    Vector(int a)
    {
        len =a;
        arr = new string[len];
    }
    Vector(const Vector &vec):len(vec.len)
    {
        arr = new string[len];
        for(int i=0;i<len;i++)
        {
            arr[i] = vec.arr[i];
        }
        
    }
    
    Vector addEntry(string newentry)
    {
        Vector temp(len+1);
        for(int i=0;i<len;i++)
        {
            temp.arr[i]=arr[i];
        }
        temp.arr[len] = newentry;
        return temp;
    }
    Vector deleteEntry(string entrytodelete)
    {
        bool find =false;
        for(int i=0;i<len;i++)
        {
            if((arr[i] == entrytodelete))
            {
                find =true;
            }
        }

        if(find == true)
        {
            bool but = true;
            Vector temp(len-1);
            temp.arr = new string[temp.len];
            int con=0;
            for(int i=0;i<len;i++,con++)
            {
                if((arr[i]==entrytodelete)&&(but==true))
                {
                    con--;
                    but = false;
                }
                else
                {
                    temp.arr[con]= arr[i];
                }
            }
            return temp;
        }
        else
        {
            Vector temp(len);
            for(int i=0;i<len;i++)
            {
                temp.arr[i]=arr[i];
            }
            return temp;
        }
    }
    ~Vector()
    {
        delete [] arr;
    }
};

int main(int argc,char* argv[])
{
    ifstream in;
    in.open("case1.txt");
    ofstream out;
    out.open("Output1.txt");
    int n;
    string dec,code;
    in>>n;
    Vector p(0);
    Vector t;
    int sum=0;
    for(int i=0;i<n;i++)
    {
        in>>dec;
        if(dec=="add")
        {
            
            in>>code;
            Vector h(p.addEntry(code));
            p.addp(h);
            //p.printfuc();
        }
        else if(dec == "delete")
        {
            in>>code;
            Vector h(p.deleteEntry(code));
            p.decp(h);
            //p.printfuc();
        }
        
        //cout<<sum++;
    }
    
    p.printfuc(out);
    return 0;
}