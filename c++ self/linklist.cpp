#include<iostream>
using namespace std;

struct list{
    int value;
    list* next;
};

int main(){

    list* head;
    head = new list();
    head->value=0;
    head->next = NULL;

    int score;
    int number;
    
    cin>>number;
    cin >> score;

    head->value = score;
    head->next = NULL;

    list* current = head;
    for(int i=0;i<number-1;i++)
    {
        cin>>score;
        current->next = new list();
        current = current->next;
        current->value = score;
        current->next = NULL;
    }//dasd

    cout<<"student score is"<<endl;

    current = head;

    for(int i=0;i<number;i++)
    {
        cout<<current->value<<endl;
        current = current -> next;
        if ( current == NULL )
        {
            break;
        }
    }
    cout<<endl;
    return 0;   
    
}


