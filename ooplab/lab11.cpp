#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class I {
    public:
    string type, name;
    int value;
    bool friend operator<(I a, I b);
    protected:
        int f;
};
bool operator<(I a, I b) {
    if (a.type < b.type) {
        return 1;
    } else if (a.type == b.type) {
        if (a.value < b.value)
            return 1;
    }
    return 0;
}
int main(int argc, char** argv) {
    ifstream in;
    in.open("input.txt");
    vector<I> item;

    while (!in.eof()) {
        string t1, t2;
        int t3;
        in >> t1 >> t2 >> t3;
        I temp;
        temp.type = t1;
        temp.name = t2;
        temp.value = t3;
        item.push_back(temp);
    }
    while (1) {
        string key;
        cin >> key;
        if (key == "-i") {
            string t1, t2;
            int t3;
            cin >> t1 >> t2 >> t3;
            I temp;
            temp.type = t1;
            temp.name = t2;
            temp.value = t3;
            bool state = false;
            for (int i = 0; i < item.size(); i++) {
                if (item[i].type == t1 && item[i].name == t2) {
                    state = true;
                    item[i].value += t3;
                }
            }

            if (state) {
                ;
            } else {
                item.push_back(temp);
            }

        } else if (key == "-s") {
            string t1, t2;
            int t3;
            cin >> t1 >> t2 >> t3;
            for (int i = 0; i < item.size(); i++) {
                if (item[i].type == t1 && item[i].name == t2)
                    item[i].value -= t3;
            }
        } else if (key == "-d") {
            string t1, t2;

            cin >> t1 >> t2;
            for (int i = 0; i < item.size(); i++) {
                if (item[i].type == t1 && item[i].name == t2)
                    cout << item[i].type << " " << item[i].name << " " << item[i].value << endl;
            }
        }

        else if (key == "-all") 
        {
            sort(item.begin(), item.end());
            for (int i = 0; i < item.size(); i++) {
                
                cout << item[i].type << " " << item[i].name << " " << item[i].value << endl;
            }
        }
    }

    return 0;
}