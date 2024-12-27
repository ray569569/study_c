/*Write a program to assign passengers seats in an airplane. Assume a small airplane
with seat numbering as follows:
1 A B C D
2 A B C D
3 A B C D
4 A B C D
5 A B C D
6 A B C D
7 A B C D
The program should display the seat pattern, with an X marking the seats already
assigned. For example, after seats 1A, 2B, and 4C are taken, the display should look
like this:
1 X B C D
2 A X C D
3 A B C D
4 A B X D
5 A B C D
6 A B C D
7 A B C D
After displaying the seats available, the program prompts for the seat desired, the
user types in a seat, and then the display of available seats is updated. This continues
until all seats are filled or until the user signals that the program should end. If the
user types in a seat that is already assigned, the program should say that that seat is
occupied and ask for another choice .If the user enters char 'q', the program is
terminated*/
#include <iostream>
#include <string>
using namespace std;

void display(char board[][4]) {
    for (int i = 0; i < 7; i++) {
        cout << i + 1 << " ";
        for (int j = 0; j < 4; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    char board[7][4];
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 'A' + j;
        }
    }
    display(board);
    int row;
    char col;
    while (true) {
        cout << "Enter the row number: ";
        cin >> row;
        if (row == 'q') {
            break;
        }
        cout << "Enter the column letter: ";
        cin >> col;
        if (col == 'q') {
            break;
        }
        if (board[row - 1][col - 'A'] == 'X') {
            cout << "That seat is already occupied." << endl;
        } else {
            board[row - 1][col - 'A'] = 'X';
        }
        display(board);
    }
    return 0;
}
