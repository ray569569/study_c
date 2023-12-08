#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
//最大深度
bool but = true;
stack<pair<int, int>> path;
bool check(pair<int, int> t, stack<pair<int, int>>& temp, char**& maze, int**& sol, int& size, int& con) {
    if (t.first >= 0 && t.first <= size - 1 && t.second <= size - 1 && t.second >= 0) {
        if (sol[t.first][t.second] > temp.size() + 1 && maze[t.first][t.second] != '#' && temp.size() < con) {
            return true;
        }
    }
    return false;
}
void updateend(stack<pair<int, int>>& temp, pair<int, int> end, int** sol, int& con) {
    if (temp.size() > 0) {
        if (temp.top().first == end.first && temp.top().second == end.second) {
                but = false;
                path = temp;
            }
        }
    }

void gonext(stack<pair<int, int>>& temp, char**& maze, int**& sol, int& size, pair<int, int> start, pair<int, int> end, int con, int& ti) {
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
        if (check(right, temp, maze, sol, size, con)) {
            temp.push(right);
            updateend(temp, end, sol, con);
            sol[right.first][right.second] = temp.size() - 1;
        } 
        else if (check(left, temp, maze, sol, size, con)) {
            temp.push(left);
            updateend(temp, end, sol, con);
            sol[left.first][left.second] = temp.size() - 1;
        }
        else if (check(down, temp, maze, sol, size, con)) {
            temp.push(down);
            updateend(temp, end, sol, con);
            sol[down.first][down.second] = temp.size() - 1;
        } 
        else if (check(up, temp, maze, sol, size, con)) {
            temp.push(up);
            updateend(temp, end, sol, con);
            sol[up.first][up.second] = temp.size() - 1;
        } 
        else {
            temp.pop();
        }
    }
    if (temp.size() > 0) {
        return gonext(temp, maze, sol, size, start, end, con, ti);
    }
}

int main() {
    int size;
    int** sol;
    char** maze;
    int con;
    int ti;
    pair<int, int> start, end;

    cin >> start.first >> start.second >> end.first >> end.second >> size;
    maze = new char*[size];
    for (int i = 0; i < size; i++) {
        maze[i] = new char[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> maze[i][j];
        }
    }
    sol = new int*[size];
    for (int i = 0; i < size; i++) {
        sol[i] = new int[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            sol[i][j] = 10000000;
        }
    }
    sol[start.first][start.second] = 0;
    stack<pair<int, int>> temp;
    temp.push(start);
    con = 1;
    while (but) {
        gonext(temp, maze, sol, size, start, end, con, ti);
        temp.push(start);
        con += 1;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sol[i][j] = 10000000;
            }
        }
        sol[start.first][start.second] = 0;
        if (con >= size * size) {
            break;
        }
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
        cout << "(" << rev.top().first << ", " << rev.top().second << ")" << " -> ";
        rev.pop();
    }
    cout << "End" << endl;
    for (int i = 0; i < size; i++) {
        delete[] sol[i];
    }
    delete[] sol;
    for (int i = 0; i < size; i++) {
        delete[] maze[i];
    }
    delete[] maze;
    return 0;
}