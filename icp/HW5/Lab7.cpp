/*Write a program that will allow two users to play tic-tac-toe. The program
should ask for moves alternately from player X and player O. The program
displays the game positions as follows:
1 2 3
4 5 6
7 8 9
The players enter their moves by entering the position number they wish
to mark. After each move, the program displays the changed board. A
sample board configuration is as follows:
X X O
4 5 6
O 8 9*/


#include <iostream>
#include <string>
using namespace std;

void display(char board[]) {
    for (int i = 0; i < 9; i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0) {
            cout << endl;
        }
    }
}

int main() {
    char board[9];
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i;
    }
    display(board);
    int move;
    string player = "X";
    for (int i = 0; i < 9; i++) {
        cout << "Player " << player << ", enter your move: ";
        cin >> move;
        board[move - 1] = player[0];
        display(board);
        if (player == "X") {
            player = "O";
        } else {
            player = "X";
        }
    }
    return 0;
}