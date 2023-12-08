#include<iostream>
using namespace std;

class Card
{
private:
    friend class Link;
    string number;
    Card* nextcard;
public:
    Card(string n="25",Card* next=nullptr):number(n),nextcard(next){};
};
class Link
{
public:
    Card* first;
    void Add(string num)
    {
        Card* temp = first;
        first = new Card(num,temp);
    }
    void Delete(string num)
    {
        if(first ==nullptr)
        {
            return ;
        }
        Card* temp;
        temp = first;
        if(first->number==num)
        {
            first = first->nextcard;
        }
        else
        {
            while(temp->nextcard!=nullptr)
            {
                if(temp->nextcard->number == num)
                {
                    temp->nextcard = temp->nextcard->nextcard;
                    break;
                }
                else
                {
                    temp=temp->nextcard;
                }
            }
        }
        return ;
    }
    void truncateFirst()
    {
        if(first==nullptr)
        {
            return ;
        }
        else
        {
            first = first->nextcard;
            return ;
        }
    }
    void truncateLast()
    {
        if(first==nullptr)
        {
            return ;
        }
        else
        {
            Card* temp=first;
            while(temp->nextcard->nextcard!=nullptr)
            {
                temp=temp->nextcard;
            }
            temp->nextcard=nullptr;
            return ;
        }
    }
    void printdeck()
    {
        Card* temp=first;
        for(;temp!=nullptr;temp=temp->nextcard)
        {
            cout<<temp->number<<" ";
        }
        return ;
    }
    Link()
    {
        first = nullptr;
    }
};

int main()
{
    Link Deck;
    int n;
    cin>>n;
    string oper;
    string num;
    for(int i=0;i<n;i++)
    {
        cin>>oper;
        if(oper=="add")
        {
            cin>>num;
            Deck.Add(num);
        }
        else if(oper == "delete")
        {
            cin>>num;
            Deck.Delete(num);
        }
        else if(oper == "truncateFirst")
        {
            Deck.truncateFirst();
        }
        else if(oper == "truncateLast")
        {
            Deck.truncateLast();
        }
    }
    Deck.printdeck();
    return 0;
}