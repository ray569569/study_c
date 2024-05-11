#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void DFS(int start,int now,int end,int size, bool** matrix,vector<vector<int>> &path,vector<int> &temp)
{
    //cout<<"dd"<<endl;
    //cout<<start<<' '<<now<<' '<<end<<' '<<size<<endl;
    if(temp[temp.size()-1]==end)
    {
        path.push_back(temp);
        temp.clear();
        //cout<<"pushed"<<endl;
        return ;
    }
    else
    {
        for(int i=0;i<size;i++)
        {
            //cout<<i<<" I am i"<<endl;
            if(matrix[now][i]==1)
            {
                vector<int > state = temp;
                temp.push_back(i);
                DFS(start,i,end,size,matrix,path,temp);
                temp = state;
            }
        }
        return ;
    }
}

int main()
{
    int number,temp1,temp2,start=0;
    vector<int > target;
    bool** connect;

    cin>>number;
    connect = new bool*[number];
    for(int i=0;i<number;i++)
    {
        connect[i] = new bool[number];
    }
    for(int i=0;i<number;i++)
    {
        for(int j=0;j<number;j++)
        {
            connect[i][j] = false;
        }
    }

    while(cin>>temp1)
    {
        cin>>temp2;
        if(temp2==-1)
        {
            target.push_back(temp1);
        }
        else
        {
            connect[temp1][temp2] = true;
        }
    }

    for(int i=0;i<number;i++)
    {
        int n=0;
        for(int j=0;j<number;j++)
        {
            if(connect[j][i] == false)
            {
                //cout<<j<<' '<<i<<endl;
                n++;
            }
        }
        //cout<<n<<' '<<number<<endl;
        if(n==number)
        {
            start = i;
            break;
        }
    }
//    cout<<start<<endl;

    vector<vector<int >> path;
    vector<int > temp;
    for(int i=0;i<target.size();i++)
    {
        temp.push_back(start);
        DFS(start,start,target[i],number,connect,path,temp);
        temp.clear();
    }
    //cout<<path.size()<<endl;
    sort(path.begin(),path.end());
    for(int i=0;i<path.size();i++)
    {
        for(int j=0;j<path.size()-1;j++)
        {
            if(path[j].size()>path[j+1].size())
            {
                vector<int > temp1 = path[j+1];
                path[j+1] = path[j];
                path[j] = temp1;
            }
        }
    }

    for(int i=0;i<path.size();i++)
    {
        for(int j=0;j<path[i].size();j++)
        {
            cout<<path[i][j]<<' ';
        }
        cout<<endl;
    }
    return 0;
}
