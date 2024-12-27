#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Heading {
private:
    string companyName;
    string reportName;

    string centerText(const string& text, int width) {
        int padding = (width - text.size()) / 2;
        string centered = string(padding, ' ') + text + string(padding, ' ');
        if (centered.size() < width) { 
            centered += " ";
        }
        return centered;
    }

public:

    Heading(string company = "ABC Industries", string report = "Report")
        : companyName(company), reportName(report) {}


    void oneLine() {
        string combined = companyName + " " + reportName;
        cout << centerText(combined, 50) << endl; 
    }


    void boxed() {
        const int width = 50;
        string border = string(width, '*');
        cout << border << endl;
        cout << centerText(companyName, width) << endl;
        cout << centerText(reportName, width) << endl;
        cout << border << endl;
    }


    void setCompany(const string& company) {
        companyName = company;
    }

    void setReport(const string& report) {
        reportName = report;
    }
};

int main() {

    Heading heading1;
    cout << "One-Line Format (Default Values):" << endl;
    heading1.oneLine();


    heading1.setCompany("Pet Pals");
    heading1.setReport("Payroll Report");
    cout << "\nBoxed Format (Modified Values):" << endl;
    heading1.boxed();

    Heading heading2("Tech Corp", "Annual Report");
    cout << "\nBoxed Format (New Object):" << endl;
    heading2.boxed();

    return 0;
}
