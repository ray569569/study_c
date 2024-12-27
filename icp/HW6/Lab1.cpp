#include <iostream>
#include <cstring> 
using namespace std;

int main() {
    const int SIZE = 50; 
    char firstName[SIZE], middleName[SIZE], lastName[SIZE], formattedName[3 * SIZE + 5];

    cout << "Enter your first name: ";
    cin.getline(firstName, SIZE);
    cout << "Enter your middle name: ";
    cin.getline(middleName, SIZE);
    cout << "Enter your last name: ";
    cin.getline(lastName, SIZE);
    
    strcpy(formattedName, lastName);          
    strcat(formattedName, ", ");             
    strcat(formattedName, firstName);         
    strcat(formattedName, " ");              
    strcat(formattedName, middleName);        

    cout << "Formatted name: " << formattedName << endl;

    return 0;
}
