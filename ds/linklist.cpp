#include<iostream>
using namespace std;
class Stacknode
{
public:
    friend class Stack;
    int data;
    Stacknode* next;
    Stacknode(int d=10,Stacknode* l=nullptr):data(d),next(l){};
};
class Stack
{
public:
    Stacknode* top;
    void ADD(int a);
    void Delete(); 
    void Reverse()
    {
        Stacknode* f =top,*b=nullptr;

        for(int i=0;i<10;i++)
        {
            Stacknode* c= b;
            b= f;
            f=f->next;
            b->next=c;
        }
        top = b;
    }
    
    Stack():top(0){};
};


void Stack::ADD(int a)
{
    Stacknode* temp = top;
    //top->data=55;
    top = new Stacknode(a,temp);
    //cout<<top->data;

    return ;
}
void Stack::Delete()
{
    return;
}
int main()
{

    Stack a;
    for(int i=0;i<10;i++)
    {
        a.ADD(i);
    }
    a.Reverse();
    for(int i=0;i<10;i++)
    {
        cout<<(a.top->data)<<endl;
        a.top = a.top->next;
    }

    return 0;
}