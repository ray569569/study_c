#include<iostream>
#include<vector>
#include<istream>
#include<sstream>
using namespace std;

class node
{
private:
    int data;
    node* left;
    node* right;
public:
    friend void postordersearch(node*); 
    friend node* buildtree(vector<int >,vector<int> ,int,int,int&);
    node(int d=-1,node* l=nullptr,node* r=nullptr):data(d),left(l),right(r){};
};

node* buildtree(vector<int> pre,vector<int> in,int lend,int rend,int& idx)
{
    if(idx>pre.size()-1)
    {
        return nullptr;
    }
    int root = pre[idx];
    int mid=lend;
    while(mid<rend)
    {
        if(in[mid] == root)
        {
            break;
        }
        mid++;
    }
    //cout<<idx<<" "<<lend<<" "<<mid<<" "<<rend<<endl;
    node* nodeleft = new node;
    node* noderight = new node;
    nodeleft = nullptr;
    noderight = nullptr;
    if(lend<mid)
    {
        idx++;
        nodeleft = buildtree(pre,in,lend,mid-1,idx);
    }
    if(rend>mid)
    {
        idx++;
        noderight = buildtree(pre,in,mid+1,rend,idx);
    }
    node* temp=new node;
    temp->left = nodeleft;
    temp->right = noderight;
    temp->data = root;
    //cout<<root<<"aa"<<endl;
    return temp;
}
void postordersearch(node* cur)
{
    if(!cur)
    {
        return ;
    }
    if(cur->left)
    {
        postordersearch(cur->left);
    }
    if(cur->right)
    {
        postordersearch(cur->right);
    }
    cout<<cur->data<<endl;
}
int main()
{
    vector<int> preorder;
    vector<int> inorder;
    string pre;
    string in;
    getline(cin,pre);
    getline(cin,in);
    stringstream ss1,ss2;
    ss1<<pre;
    ss2<<in;
    while(ss1)
    {
        int temp;
        ss1>>temp;
        preorder.push_back(temp);
    }
    while(ss2)
    {
        int temp;
        ss2>>temp;
        inorder.push_back(temp);
    }
    int id=0;
    node* root;
    root = new node;
    root = buildtree(preorder,inorder,0,preorder.size()-2,id);
    postordersearch(root);
    return 0;
}
