#include<iostream>
#include<vector>
using namespace std;

class tree_node
{
public:
    long long value;
    long long lower_num;
    tree_node* left;
    tree_node* right;
    tree_node* parant;
    bool color; //true red
};

class RBtree
{
public:
    tree_node* root;
    tree_node* TNULL;
    RBtree() 
    {
        TNULL = new tree_node();
        TNULL->color = false;  
        root = TNULL;
    }
};

void tree_insert(RBtree &T, long long a);
void tree_insert_fix(RBtree &T, tree_node* node_a);
void rotate_left(RBtree &T, tree_node* node_a);
void rotate_right(RBtree &T, tree_node* node_a);
void inorder(RBtree T, tree_node* node_a);
long long count_less(RBtree,long long );
long long countRangeSum(vector<long long>& nums, long long lower, long long upper);
int main()
{
    vector<long long> input;
    long long temp;
    RBtree tree;

    while(cin>>temp)
    {
        input.push_back(temp);
    }
    long long a,b;
    b = input[input.size()-1];
    a = input[input.size()-2];
    input.pop_back();
    input.pop_back();
    cout<<countRangeSum(input,a,b);
    
    //inorder(tree,tree.root);
    //cout<<endl;
    //cout<<count_less(tree,700);

    return 0;
}

void tree_insert(RBtree &T, long long a)
{
    tree_node* x;
    tree_node* y;
    tree_node* node_a;
    node_a = new tree_node();
    node_a->value = a;
    node_a->lower_num = 0;
    node_a->parant = T.TNULL;
    y = T.TNULL; //upper
    x = T.root; //lower
    while(x != T.TNULL)
    {
        y = x;
        if(a < x->value)
        {
            y->lower_num+=1;
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    
    node_a->parant = y;
    if(y == T.TNULL) //FIRST time
    {
        T.root = node_a;
    }
    else if(a < y->value)
    {
        y->left = node_a;
    }
    else //if same than seem it as bigger
    {
        y->right = node_a;
    }
    node_a->left = T.TNULL;
    node_a->right = T.TNULL;
    node_a->color = 1;
    tree_insert_fix(T,node_a);
    return ;
}

void tree_insert_fix(RBtree &T, tree_node* node_a)
{
    tree_node* y;
    y = new tree_node();
    while(node_a->parant->color == 1)
    {
        
        if(node_a->parant == node_a->parant->parant->left)
        {
            
            y = node_a->parant->parant->right;
            if(y->color == 1)
            {
                node_a->parant->color = 0;
                y->color = 0;
                y->parant->color = 1;
                node_a = node_a->parant->parant;
            }
            else 
            {
                if(node_a == node_a->parant->right)
                {   
                    node_a = node_a->parant;
                    rotate_left(T,node_a);
                }
                node_a->parant->color = 0;
                node_a->parant->parant->color = 1;
                rotate_right(T,node_a->parant->parant);
                return ;
            }
        }
        else 
        {
            y = node_a->parant->parant->left;
            if(y->color == 1)
            {
                node_a->parant->color = 0;
                y->color = 0;
                y->parant->color = 1;
                node_a = node_a->parant->parant;
                
            }
            else
            {
                if(node_a == node_a->parant->left)
                {
                    node_a = node_a->parant;
                    rotate_right(T,node_a);
                }
                node_a->parant->color = 0;
                node_a->parant->parant->color = 1;
                rotate_left(T,node_a->parant->parant);
                return ;
            }
        }
    }
    T.root->color = 0;
    return ;
}

void rotate_left(RBtree &T, tree_node* node_a)
{
    tree_node* y;
    y = node_a->right;
    node_a->right = y->left;
    if(y->left != T.TNULL)
    {
        y->left->parant = node_a; //y child's parant
    }
    y->parant = node_a->parant;
    if(node_a->parant == T.TNULL)
    {
        T.root = y;
    }
    else if(node_a == node_a->parant->left)
    {
        node_a->parant->left = y;
    }
    else
    {
        node_a->parant->right = y;
    }
    y->left = node_a;
    node_a->parant = y;
    bool t;
    t = y->color;
    y->color = node_a->color;
    node_a->color = t;
    y->lower_num+=node_a->lower_num+1;
    return ;
}

void rotate_right(RBtree &T, tree_node* node_a)
{
    tree_node* y;
    y = node_a->left;
    node_a->left = y->right;
    if(y->right != T.TNULL)
    {
        y->right->parant = node_a; //y child's parant
    }
    y->parant = node_a->parant;
    if(node_a->parant == T.TNULL)
    {
        T.root = y;
    }
    else if(node_a == node_a->parant->left)
    {
        node_a->parant->left = y;
    }
    else
    {
        node_a->parant->right = y;
    }
    y->right = node_a;
    node_a->parant = y;
    bool t;
    t = y->color;
    y->color = node_a->color;
    node_a->color = t;
    node_a->lower_num-=(y->lower_num+1);
}

void inorder(RBtree T, tree_node* node_a) {
    if (node_a == T.TNULL) {  
        return;
    }
    inorder(T, node_a->left);
    cout << node_a->value << " "<<count_less(T,node_a->value)<<endl;
    inorder(T, node_a->right);
}

long long count_less(RBtree T,long long num)
{
    tree_node* t;
    t = T.root;
    long long count = 0;
    while((t!=T.TNULL))
    {
        if(t->value>num && t->left!=T.TNULL)
        {
            t = t->left;
        }
        else if(t->value<=num && t->right!=T.TNULL)
        {
            count+=t->lower_num+1;
            t = t->right;
        }
        else
        {
            break;
        }
    }
    return t->lower_num + count + (t->value<=num);
}

long long countRangeSum(vector<long long>& nums, long long lower, long long upper) 
{
    RBtree tree;
    long long prefixSum = 0;
    long long count = 0;

    tree_insert(tree,0);

    for (long long i=0;i<nums.size();i++) {
        prefixSum += nums[i];
        count += count_less(tree, prefixSum - lower) - count_less(tree, prefixSum - upper-1);
        tree_insert(tree,prefixSum);
    }

    return count;
}