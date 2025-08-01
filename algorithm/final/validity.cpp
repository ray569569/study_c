#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cassert>
#include <iomanip>
#include <fstream>
using namespace std;

class Validator {
private:
    int maxCapacity;
    vector<int> memories;         // agent memory requirements
    vector<vector<int>> teams;    // teams containing agents
    
    // Output results
    int reportedCost;            // reported total cost
    int serverCount;             // number of servers used
    vector<int> assignments;      // agent assignment results

    // Validate basic format
    bool validateBasicFormat(const string& outputFile) {
        ifstream outF(outputFile);
        if (!outF) {
            cout << "Error: Unable to open output file" << endl;
            return false;
        }

        // Read cost
        if (!(outF >> reportedCost)) {
            cout << "Error: Unable to read cost value" << endl;
            return false;
        }

        // Read server count
        if (!(outF >> serverCount)) {
            cout << "Error: Unable to read server count" << endl;
            return false;
        }

        // Check server count validity
        if (serverCount < 2) {
            cout << "Error: Server count must be at least 2, currently " << serverCount << endl;
            return false;
        }

        // Read assignments
        assignments.resize(memories.size());
        for (size_t i = 0; i < memories.size(); i++) {
            if (!(outF >> assignments[i])) {
                cout << "Error: Incomplete agent assignment information" << endl;
                return false;
            }
            if (assignments[i] < 0 || assignments[i] >= serverCount) {
                cout << "Error: Server ID " << assignments[i] << " out of range [0, " 
                     << serverCount - 1 << "]" << endl;
                return false;
            }
        }

        // Check for extra data
        int temp;
        if (outF >> temp) {
            cout << "Error: Output file contains extra data" << endl;
            return false;
        }

        return true;
    }

    // Validate memory constraints
    bool validateMemoryConstraints() {
        vector<int> serverLoads(serverCount, 0);
        vector<vector<int>> serverAgents(serverCount);  // Record agents on each server
        
        for (size_t i = 0; i < memories.size(); i++) {
            int server = assignments[i];
            serverLoads[server] += memories[i];
            serverAgents[server].push_back(i);
            
            if (serverLoads[server] > maxCapacity) {
                cout << "Error: Server " << server << " memory usage (" 
                     << serverLoads[server] << ") exceeds limit (" << maxCapacity << ")" << endl;
                cout << "Agents assigned to this server: ";
                for (int agent : serverAgents[server]) {
                    cout << agent << "(" << memories[agent] << ") ";
                }
                cout << endl;
                return false;
            }
        }
        
        // Print memory usage for each server
        cout << "\nMemory usage:" << endl;
        cout << setw(10) << "Server" << setw(15) << "Usage" << setw(15) 
             << "Usage Rate" << setw(20) << "Number of Agents" << endl;
        cout << string(60, '-') << endl;
        
        for (int i = 0; i < serverCount; i++) {
            double usage = serverLoads[i] * 100.0 / maxCapacity;
            cout << setw(10) << i 
                 << setw(15) << serverLoads[i] 
                 << setw(14) << fixed << setprecision(1) << usage << "%"
                 << setw(20) << serverAgents[i].size() << endl;
        }
        
        return true;
    }

    // Calculate actual cost and validate team distribution
    bool validateTeamDistribution() {
        int totalCost = 0;
        cout << "\nTeam distribution:" << endl;
        cout << setw(8) << "Team" << setw(15) << "Spanning Servers" 
             << setw(12) << "Cost" << setw(20) << "Server Distribution" << endl;
        cout << string(55, '-') << endl;
        
        for (size_t i = 0; i < teams.size(); i++) {
            unordered_set<int> usedServers;
            for (int agentId : teams[i]) {
                usedServers.insert(assignments[agentId]);
            }
            
            int serversSpanned = usedServers.size();
            int teamCost = (serversSpanned - 1) * (serversSpanned - 1);
            totalCost += teamCost;
            
            // Display distribution for each team
            cout << setw(8) << i 
                 << setw(15) << serversSpanned 
                 << setw(12) << teamCost 
                 << setw(20);
            
            cout << "{";
            bool first = true;
            for (int server : usedServers) {
                if (!first) cout << ",";
                cout << server;
                first = false;
            }
            cout << "}" << endl;
        }
        
        cout << "\nTotal Cost: " << totalCost << endl;
        if (totalCost != reportedCost) {
            cout << "Error: Reported cost (" << reportedCost << ") does not match calculated cost (" 
                 << totalCost << ")" << endl;
            return false;
        }
        
        return true;
    }

public:
    bool loadInput(const string& inputFile) {
        ifstream inF(inputFile);
        if (!inF) {
            cout << "Error: Unable to open input file" << endl;
            return false;
        }

        // Read max capacity
        inF >> maxCapacity;

        string line;
        getline(inF, line);  // Read remaining newline

        // Read .agent section
        while (getline(inF, line)) {
            if (line == ".agent") break;
        }

        // Read number of agents and memory requirements
        int n;
        inF >> n;
        memories.resize(n);
        for (int i = 0; i < n; i++) {
            inF >> memories[i];
        }

        // Read .team section
        while (getline(inF, line)) {
            if (line == ".team") break;
        }

        // Read team information
        int m;
        inF >> m;
        teams.resize(m);
        for (int i = 0; i < m; i++) {
            int teamSize;
            inF >> teamSize;
            teams[i].resize(teamSize);
            for (int j = 0; j < teamSize; j++) {
                inF >> teams[i][j];
            }
        }

        return true;
    }

    bool validate(const string& outputFile) {
        cout << "\nStarting validation of output results..." << endl;
        cout << "===================" << endl;
        
        // Check basic format
        if (!validateBasicFormat(outputFile)) {
            return false;
        }

        // Check memory constraints
        if (!validateMemoryConstraints()) {
            return false;
        }

        // Check team distribution and cost calculation
        if (!validateTeamDistribution()) {
            return false;
        }
        
        // Print validation passed information
        cout << "\nValidation result: Passed " << endl;
        cout << "- Total cost: " << reportedCost << endl;
        cout << "- Used " << serverCount << " servers" << endl;
        cout << "- All memory constraints and team distribution rules are met" << endl;
        
        return true;
    }
};

int main() {
    
    Validator validator;
    
    // Load input file
    validator.loadInput("./advanced/ISPD98_ibm02.txt");

    // Validate output results
    bool isValid = validator.validate("output.txt");
    
    cout << (isValid ? "ok" : "error") << endl;

    return isValid ? 0 : 1;
}
