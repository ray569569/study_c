#include <iostream>
#include <string>
using namespace std;

struct MovieData
{
    string title;
    string director;
    int year;
    int runningTime;
    MovieData(string t, string d, int y, int r)
    {
        title = t;
        director = d;
        year = y;
        runningTime = r;
    }
};

void display(MovieData m)
{
    cout << "Title : " << m.title << endl;
    cout << "Director : " << m.director << endl;
    cout << "Released : " << m.year << endl;
    cout << "Running Time: " << m.runningTime << " minutes" << endl;
}

int main()
{
    string input;
    cout << "Enter the movie details (Title, Director, Year, Running Time) separated by commas: ";
    getline(cin, input);

    size_t pos = 0;
    string token;
    string details[4];
    int i = 0;

    while ((pos = input.find(',')) != string::npos && i < 4) {
        token = input.substr(0, pos);
        details[i++] = token;
        input.erase(0, pos + 1);
    }
    details[i] = input; // Last part after the final comma

    string t = details[0];
    string d = details[1];
    int y = stoi(details[2]);
    int r = stoi(details[3]);

    MovieData m1(t, d, y, r);
    display(m1);

    return 0;
}