#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int num = rand()%100;

class Player
{
public:
    virtual int getGuess()
    {
        return 0;
    }
};
class ComputerPlayer:public Player
{
public:
    int getGuess();
};

class HumanPlayer:public Player
{
public:
    int getGuess();
};
int ComputerPlayer::getGuess()
{
    int n = rand()%100;
    return n;
}
int HumanPlayer::getGuess()
{
    cout<<"Please enter an number: ";
    int n;
    cin>>n;
    return n;
}

bool checkForWin(int guess,int answer)
{
    cout<<"You guessed "<<guess<<".";
    if(answer == guess)
    {
        cout<<"You're right! You win!"<<endl;
        return true;
    }
    else if(answer<guess)
    {
        cout<<"Your guess is too high."<<endl;
    }
    else
    {
        cout<<"Your guess is too low."<<endl;
    }
    return false;
}

void play(Player &player1,Player &player2)
{
    int answer = 0,guess =0;
    answer = rand()%100;
    bool win = false;

    /*For Demo*/
    string str;
    cout<<"Show the answer? (yes/no): ";
    cin>>str;
    if(str == "yes")
    {
        cout<<"The answer is "<<answer<<endl;
    }
    /*End*/
    while(!win)
    {
        cout<<"Player 1's turn to guess."<<endl;
        guess = player1.getGuess();
        win = checkForWin(guess,answer);
        if(win)return ;
        cout<<"Player 2's turn to guess."<<endl;
        guess = player2.getGuess();
        win = checkForWin(guess,answer);
    }
}

int main(int argc, const char** argv) 
{   
    srand(time(NULL));
    cout<<"Please choose the gamemode (0:PvP, 1:PvC, 2:CvC): ";
    int x;
    cin>>x;
    if(x == 0)
    {
        HumanPlayer a;
        HumanPlayer b;
        play(a,b);
    }
    else if(x == 1)
    {
        HumanPlayer a;
        ComputerPlayer b;
        play(a,b);
    }
    else
    {
        ComputerPlayer a;
        ComputerPlayer b;
        play(a,b);
    }
    return 0;
}