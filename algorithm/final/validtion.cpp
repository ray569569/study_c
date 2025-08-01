#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<set>
#include <unordered_map>
using namespace std;

int main() {
    ifstream in1("./basic/ISPD98_ibm02.txt");
    ifstream in2("output.txt");
    string line1, line2;
    
    int cost1,cost2;
    int maxDiskCapacity;
    int numServers1,numServers2;
    in2>>cost2;
    in2>>numServers2;

    vector<int > assignments2;
    vector<int > weights;
    while(in2>>line2){
        if(line2==""){
            break;
        }
        assignments2.push_back(stoi(line2));
    }

    long long n, m;
    int totalCost=0;
    in1 >> maxDiskCapacity;
    in1 >> line1;

    if (line1 == ".agent") {
        in1 >> n;
        for (long long i = 0; i < n; i++) {
            in1 >> line1;
            weights.push_back(stoi(line1));
        }
    } else {
        cout << "Error: .agent not found" << endl;
        return 0;
    }
    in1 >> line1;
    vector<int > teams;
    if (line1 == ".team") {
        in1 >> n;
        for (long long i = 0; i < n; i++) {
            in1 >> m;
            for (long long j = 0; j < m; j++) {
                in1 >> line1;
                teams.push_back(stoi(line1));
            }

            //cost calculation
            set<int> servers;

            for(int j=0;j<teams.size();j++){
                //cout<<i<<" "<<j<<endl<<endl;
                //cout<< teams[j] <<" " <<assignments2[teams[j]]<<endl;
                servers.insert(assignments2[teams[j]]);
            }
            totalCost+=pow(servers.size()-1,2);
            teams.clear();
        }
    } else {
        cout << "Error: .team not found" << endl;
        return 0;
    }
    if(totalCost!=cost2){
        cout<<totalCost<<" "<<cost2<<endl;
        cout<<"Error: cost mismatch"<<endl;
        return 0;
    }
    //server capacity check
    int serverCapacity[numServers2];
    for(int i=0;i<numServers2;i++){
        serverCapacity[i]=0;
    }
    for(int i=0;i<assignments2.size();i++){
        serverCapacity[assignments2[i]]+=weights[i];
    }
    for(int i=0;i<numServers2;i++){
        if(serverCapacity[i]>maxDiskCapacity){
            cout<<"Error: Server capacity exceeded"<<endl;
            return 0;
        }
    }
    

    cout<<"Validation successful"<<endl;
    

    return 0;
}