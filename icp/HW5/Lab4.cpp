/*Write a program that lets a maker of chips and salsa keep track of their sales for five
different types of salsa they produce: mild, medium, sweet, hot, and zesty. It should
use two parallel five-element arrays: an array of strings that holds the five salsa
names and an array of integers that holds the number of jars sold during the past
month for each salsa type. The salsa names should be stored using an initialization
list at the time the name array is created. The program should prompt the user to
enter the number of jars sold for each type. Once this sales data has been entered,
the program should produce a report that displays sales for each salsa type, total
sales, and the names of the highest selling and lowest selling products*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    string salsa[] = {"mild", "medium", "sweet", "hot", "zesty"};
    int sales[5];
    int total = 0;
    for (int i = 0; i < 5; i++) {
        cout << "Enter the number of jars sold for " << salsa[i] << " salsa: ";
        cin >> sales[i];
        total += sales[i];
    }
    cout << "Sales report:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << salsa[i] << " salsa: " << sales[i] << " jars" << endl;
    }
    cout << "Total sales: " << total << " jars" << endl;
    int max = sales[0], min = sales[0];
    string maxSalsa = salsa[0], minSalsa = salsa[0];
    for (int i = 1; i < 5; i++) {
        if (sales[i] > max) {
            max = sales[i];
            maxSalsa = salsa[i];
        }
        if (sales[i] < min) {
            min = sales[i];
            minSalsa = salsa[i];
        }
    }
    cout << "The highest selling product is " << maxSalsa << " salsa with " << max << " jars" << endl;
    cout << "The lowest selling product is " << minSalsa << " salsa with " << min << " jars" << endl;
    return 0;
}