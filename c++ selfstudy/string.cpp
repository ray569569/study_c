#include<iostream>
#include<string>
using namespace std;

class term
{
public:
    int degree;
    int coef;
    term* nextterm;
public:
    term(int d = 0,int c = 5,term* next = nullptr):degree(d),coef(c),nextterm(next){};
};
class polynomial
{
private:
    friend polynomial add(polynomial,polynomial,char);
    term* first;
public:
    void newterm(int newdegree,int newcoef)
    {
        term* temp = first;
        first = new term(newdegree,newcoef,temp);
    }
    void printpolynomial()
    {
        term* temp=first;
        if(temp->coef!=1)
        {
            cout<<temp->coef;
        }
        else
        {
            ;
        }
        if(temp->degree==0)
        {
            ;
        }
        else if(temp->degree==1)
        {
            cout<<'x';
        }
        else
        {
            cout<<"x^"<<temp->degree;
        }
        temp = temp->nextterm;
        for(;temp!=nullptr;temp=temp->nextterm)
        {
            if(temp->coef>0&&temp->coef!=1)
            {
                cout<<"+"<<temp->coef;
            }
            else if(temp->coef==1)
            {
                cout<<"+";
            }
            else
            {
                cout<<temp->coef;
            }
            if(temp->degree==0)
            {
                continue;
            }
            else if(temp->degree==1)
            {
                cout<<'x';
            }
            else
            {
                cout<<"x^"<<temp->degree;
            }
        }
    }
    polynomial()
    {
        first = nullptr;
    }
};

polynomial add(polynomial A, polynomial B,char op)
{
    int count = 0;
    int coef = 0;
    term* tempA = A.first;
    term* tempB = B.first;
    polynomial final;
    
    while(A.first!=nullptr||B.first!=nullptr)
    {
        while(tempA!=nullptr)
        {
            if(A.first->degree == count)
            {
                coef += A.first->coef;
                term* t = A.first;
                A.first=A.first->nextterm;
                tempA = A.first;
                delete [] t;
            }
            else
            {
                if(tempA->nextterm!=nullptr&&tempA->nextterm->degree==count)
                {
                    coef+=tempA->nextterm->coef;
                    term* t = tempA->nextterm;
                    tempA->nextterm = tempA->nextterm->nextterm;
                    delete [] t;
                }
                else
                {
                    tempA = tempA->nextterm;
                }
            }
        }

        while(tempB!=nullptr)
        {
            if(B.first->degree == count)
            {
                if(op=='+')
                {
                    coef += B.first->coef;
                    term* t=B.first;
                    B.first=B.first->nextterm;
                    tempB = B.first;
                    delete [] t;
                }
                else
                {
                    coef -= B.first->coef;
                    term* t=B.first;
                    B.first=B.first->nextterm;
                    tempB = B.first;
                    delete [] t;
                }
            }
            else
            {
                if(tempB->nextterm!=nullptr&&tempB->nextterm->degree==count)
                {
                    if(op=='+')
                    {
                        coef+=tempB->nextterm->coef;
                        term* t = tempB->nextterm;
                        tempB->nextterm = tempB->nextterm->nextterm;
                        delete [] t;
                    }
                    else
                    {
                        coef-=tempB->nextterm->coef;
                        term* t = tempB->nextterm;
                        tempB->nextterm = tempB->nextterm->nextterm;
                        delete [] t;
                    }
                }
                else
                {
                    tempB = tempB->nextterm;
                }
            }
        }
        if(coef!=0||(coef==0&&count==0))
        {
            final.newterm(count,coef);        
        }
        coef=0;
        tempA = A.first;
        tempB = B.first;
        count++;
    }
    return final;
}

void insert(string &a,polynomial &A)
{
    string degree;
    string coef;
    int count=0;
    if(a[0]!='x')
    {
        coef=a[0];
        a.erase(0,1);
    }
    else
    {
        coef = '+';
    }
    if(a.find('+')!=string::npos||a.find('-')!=string::npos)
    {
        while(1)
        {
            if(!isdigit(a[count]))
            {
                coef += a.substr(0,count);
                a.erase(0,count);
                break;
            }
            count+=1;
        }
        if(coef.size()==1&&(coef[0]=='+'||coef[0]=='-'))
        {
            coef+='1';
        }
        count=0;
        if(a[count+1]=='^'&&a[count]=='x')
        {
            a.erase(0,count+2);
            while(1)
            {
                if(!isdigit(a[count]))
                {
                    degree = a.substr(0,count);
                    a.erase(0,count);
                    break;
                }   
                count++;
            }
        }
        else if(a[count+1]!='^'&&a[count]=='x')
        {
            a.erase(0,count+1);
            degree = '1';
        }
        else if(a[count]!='x')
        {
            degree = '0';
        }
    }
    else if(a.size()!=0)
    {
        while(count+1<=a.size())
        {
            if(!isdigit(a[count]))
            {
                coef += a.substr(0,count);
                a.erase(0,count);
                break;
            }
            else if(count+1==a.size())
            {
                coef+=a.substr(0,count+1);
                a.erase(0,count+1);
                degree='0';
                A.newterm(stoi(degree),stoi(coef));
                return;
            }
            count+=1;
        }
        if(coef.size()==1&&(coef[0]=='+'||coef[0]=='-'))
        {
            coef+='1';
        }
        count=0;
        if(a[count+1]=='^'&&a[count]=='x')
        {
            a.erase(0,count+2);
            while(1)
            {
                if(count+1==a.size())
                {
                    degree = a.substr(0,count+1);
                    a.erase(0,count+1);
                    break;
                }   
                count++;
            }
        }
        else if(a.size()==1)
        {
            a.erase(0,1);
            degree = '1';
        }
    }
    else
    {
        degree='0';
    }
    A.newterm(stoi(degree),stoi(coef));
}
int main()
{
    polynomial A;
    polynomial B;
    string a;
    string b;
    string coef;
    string degree;
    int op1;
    int op2;
    char oper;
    cin>>a>>b>>oper;

    
    while(a.size()!=0)
    {
        insert(a,A);
    }
    while(b.size()!=0)
    {
        insert(b,B);
    }
    add(A,B,oper).printpolynomial();
    return 0;
}