#include<iostream>
#include<vector>
#include<ctime> 
using namespace std;

class point
{
public:
    int value;
    bool visited;
    point()
    {
        int value = 0; 
        bool visited = false;
    }
};

void visit(vector<vector<point>> &matrix, int i, int j)
    {
        if(i<0 || j<0 || i>=6 || j>=6 || matrix[i][j].value == 0 || matrix[i][j].visited == true)
        {
            return;
        }
        matrix[i][j].visited = true;
        visit(matrix,i+1,j);
        visit(matrix,i-1,j);
        visit(matrix,i,j+1);
        visit(matrix,i,j-1);
    }

int main()
{
    srand(0);
    vector<vector<point>> matrix;
    int n = 6;
    for(int i=0;i<n;i++)
    {
        vector<point> temp;
        for(int j=0;j<n;j++)
        {
            point p;
            p.value = rand()%2;
            p.visited = false;
            temp.push_back(p);
        }
        matrix.push_back(temp);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<matrix[i][j].value<<" ";
        }
        cout<<endl;
    }
    
    int count = 0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(matrix[i][j].value == 1 && matrix[i][j].visited == false)
            {
                count++;
                visit(matrix,i,j);
            }
            
        }
    }   
    cout<<"Number of connected components: "<<count;
    return 0;
}
