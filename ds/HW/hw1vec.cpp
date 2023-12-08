#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
//跑完整張圖
int con = 0;
stack<pair<int, int>> path;
bool check(pair<int, int> t, stack<pair<int, int>>& temp, vector<vector<char>>& maze,vector<vector<int>>& sol, int& size) {
    if (t.first >= 0 && t.first <= size - 1 && t.second <= size - 1 && t.second >= 0) {
        if (sol[t.first][t.second] > temp.size() + 1 && maze[t.first][t.second] != '#') {
            return true;
        }
    }
    return false;
}
void updateend(stack<pair<int, int>>& temp, pair<int, int> end, vector<vector<int>> sol) {
    if (temp.size() > 0) {
        if (temp.top().first == end.first && temp.top().second == end.second) {
            // con++;
            //  cout<<sol[end.first][end.second]<<"dd"<<temp.size()<<endl;
            if (sol[end.first][end.second] > temp.size()) {
                path = temp;
            }
        }
    }
}
void gonext(stack<pair<int, int>>& temp, vector<vector<char>>& maze, vector<vector<int>>& sol, int& size, pair<int, int> start, pair<int, int> end,int &ti) {
    pair<int, int> up, down, left, right;
    if (temp.size() > 0) {
        up.first = temp.top().first - 1;
        up.second = temp.top().second;
        down.first = temp.top().first + 1;
        down.second = temp.top().second;
        left.first = temp.top().first;
        left.second = temp.top().second - 1;
        right.first = temp.top().first;
        right.second = temp.top().second + 1;
        if (check(right, temp, maze, sol, size)) {
            temp.push(right);
            updateend(temp, end, sol);
            sol[right.first][right.second] = temp.size();
        } else if (check(left, temp, maze, sol, size)) {
            temp.push(left);
            updateend(temp, end, sol);
            sol[left.first][left.second] = temp.size();
        }

        else if (check(down, temp, maze, sol, size)) {
            temp.push(down);
            updateend(temp, end, sol);
            sol[down.first][down.second] = temp.size();
        } else if (check(up, temp, maze, sol, size)) {
            temp.push(up);
            updateend(temp, end, sol);
            sol[up.first][up.second] = temp.size();
        } else {
            temp.pop();
        }

        // cout<<temp.top().first<<" "<<temp.top().second<<" "<<temp.size()<<endl;
    }
    // cout<<temp.top().first<<" "<<temp.top().second<<endl;
    if (temp.size() > 0 ) {
        // cout<<temp.size()<<endl;
        ti++;
        return gonext(temp, maze, sol, size, start, end,ti);
    }
}

int main() {
    int size;
    int ti=0;
    vector<vector<int> > sol;
    vector<vector<char> > maze;
    pair<int, int> start, end;
    vector<char> ma;
    vector<int > s;
    cin >> start.first >> start.second >> end.first >> end.second >> size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            char r;
            cin >>r ;
            ma.push_back(r);
        }
        maze.push_back(ma);
        ma.clear();
    }
    
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            s.push_back(1000000);
        }
        sol.push_back(s);
    }
    sol[start.first][start.second] = 0;
    stack<pair<int, int>> temp;
    temp.push(start);
    gonext(temp, maze, sol, size, start, end,ti);
    // cout<<path.size()<<endl;
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            cout << setw(7) << sol[i][j] << " ";
        }
        cout << endl;
    }
    int a = path.size();
    if (a == 0) {
        cout << "No path found!" << endl;
        return 0;
    }
    stack<pair<int, int>> rev;
    for (int i = 0; i < a; i++) {
        rev.push(path.top());
        path.pop();
    }
    cout << "Shortest Path: Start -> ";
    for (int i = 0; i < a; i++) {
        cout << "(" << rev.top().first << ", " << rev.top().second << ")"<< " -> ";
        rev.pop();
    }
    cout << "End" << endl;
    cout<<ti;
    return 0;
}