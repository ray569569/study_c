#include <iomanip>
#include <iostream>
using namespace std;

double averageVelocity(double distanceXY, double distanceYZ, double timeXY, double timeYZ) {
    return (distanceXY + distanceYZ) / (timeXY + timeYZ);
}
int main() {
    double distanceXY, distanceYZ, timeXY, timeYZ;
    cout << "Enter the distance between city X and city Y in kilometers: ";
    cin >> distanceXY;
    cout << "Enter the distance between city Y and city Z in kilometers: ";
    cin >> distanceYZ;
    cout << "Enter the time taken to go from city X to city Y in hours: ";
    cin >> timeXY;
    cout << "Enter the time taken to go from city Y to city Z in hours: ";
    cin >> timeYZ;
    cout << "Average velocity: " << fixed << setprecision(2) << averageVelocity(distanceXY, distanceYZ, timeXY, timeYZ) << " km/h" << endl;
    return 0;
}