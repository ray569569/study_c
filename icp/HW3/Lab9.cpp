#include <iostream>
using namespace std;

double toPound(double tons) {
    return tons * 2240;
}

double toKilogram(double tons) {
    return tons * 1016.05;
}

int main() {
    cout << "Tons\tPounds\tKilograms" << endl;
    for (int tons = 2; tons <= 20; tons += 2) {
        cout << tons << "\t" << toPound(tons) << "\t" << toKilogram(tons) << endl;
    }

    return 0;
}
