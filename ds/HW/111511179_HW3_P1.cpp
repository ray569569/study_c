#include<iostream>
#include<vector>
#include<istream>
#include<sstream>
#include<queue>
using namespace std;

class node
{
private:
    int data;
    node* left;
    node* right;
public:
    friend vector<int > rightsideview(node*); 
    friend node* buildtree(vector<int >,vector<int> ,int,int,int&);
    node(int d=-1,node* l=nullptr,node* r=nullptr):data(d),left(l),right(r){};
};
vector<int > rightsideview(node* root)
{
    vector<int > view;
    if(!root)
    {
        return view;
    }
    queue<node* > temp;
    temp.push(root);
    while(!temp.empty())
    {
        view.push_back(temp.back()->data);
        int size = temp.size();
        for(int i=0;i<size;i++)
        {
            node* f=temp.front();
            temp.pop();
            if(f->left)
                temp.push(f->left);
            if(f->right)
                temp.push(f->right);
        }
    }
    return view;
}
node* buildtree(vector<int> in,vector<int> post,int lend,int rend,int& idx)
{
    if(idx<0)
    {
        return nullptr;
    }
    int root = post[idx];
    int mid=lend;
    while(mid<rend)
    {
        if(in[mid] == root)
        {
            break;
        }
        mid++;
    }
    //cout<<idx<<" "<<lend<<" "<<mid<<" "<<rend<<" "<<root<<endl;
    node* nodeleft = new node;
    node* noderight = new node;
    nodeleft = nullptr;
    noderight = nullptr;
    if(rend>mid)
    {
        idx--;
        noderight = buildtree(in,post,mid+1,rend,idx);
    }
    if(lend<mid)
    {
        idx--;
        nodeleft = buildtree(in,post,lend,mid-1,idx);
    }
    node* temp=new node;
    temp->left = nodeleft;
    temp->right = noderight;
    temp->data = root;
    //cout<<root<<"aa"<<endl;
    return temp;
}

int main()
{
    vector<int> inorder;
    vector<int> postorder;
    string in;
    string post;
    getline(cin,in);
    getline(cin,post);
    stringstream ss1,ss2;
    ss1<<in;
    ss2<<post;
    while(ss1)
    {
        int temp;
        ss1>>temp;
        inorder.push_back(temp);
    }
    while(ss2)
    {
        int temp;
        ss2>>temp;
        postorder.push_back(temp);
    }
    int id=postorder.size()-2;
    node* root;
    root = new node;    
    root = buildtree(inorder,postorder,0,inorder.size()-2,id);
    vector<int > v = rightsideview(root);
    for(int i=0;i<v.size();i++)
    {
        cout<<v[i]<<endl;
    }
    return 0;
}
