#include<iostream>
using namespace std;

struct tree
{
    int value;
    tree* before;
    tree* right;
    tree* left;/* data */
};
tree* newnode(int x,tree* bef);

int main()
{
    tree* head;
    head = new tree();
    int number;
    cin>>number;

    head->value = number;
    head->before = NULL;
    head->right = NULL;
    head->left = NULL;

    tree* current;
    tree* temp;
    current = head;

    for(int j=0;j<10;j++)
    {
        cin>>number;
        while(1)
        {
            if(number>current->value)
            {
                if(current->right != NULL)
                {
                    temp = current;
                    current = current->right;
                    temp ->right =current;
                    current->before = temp;
                }
                else if(current->right == NULL)
                {
                    temp = current;
                    current = newnode(number,temp);
                    temp->right = current;
                    break;
                }      
            }

            else if(number<current->value)
            {
                if(current->left != NULL)
                {
                    temp = current;
                    current = current->left;
                    temp ->left =current;
                    current->before = temp;
                }
                else if(current->left == NULL)
                {
                    temp = current;
                    current = newnode(number,temp);
                    temp->left = current;
                    break;
                }   
            }
            else
            {
                break;
            }

        }
        current = head;    
    }

    cout<<"give a number"<<endl;
    cin>>number;
    current = head;

    while(1)
    {
        if(current->value>number)
        {
            current = current->left;
        }
        else if(current->value <number)
        {
            current = current->right;
        }
        else 
        break;
    }

    while(current->before != NULL)
    {
        cout<<current->value<<endl;
        current = current->before;
    }
    cout<<head->value<<endl;
    
    delete current;
    delete head;
    return 0;
        
    

}

tree* newnode(int x,tree* bef)
{
    tree* a= new tree();
    a->value = x;
    a->right = a->left = NULL;
    a->before = bef;
    return a;
}