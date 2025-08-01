#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

class Node {
public:
    long long id;
    long long weight; 
    long long server; 
};

class Edge {
public:
    vector<long long> members; 
    long long total_weight; 
    long long edge_cost;    
};

long long maxDiskCapacity;
vector<Node> nodes;       // Agent
vector<Edge> edges;       // TEAM
vector<int> assignments; 

long long calculateCost() {
    long long totalCost = 0;
    unordered_map<int, set<int>> teamServers;

    for (const auto &edge : edges) {
        set<int> servers;
        for (long long member : edge.members) {
            servers.insert(assignments[member]);
        }
        totalCost += pow(servers.size() - 1, 2);
    }
    return totalCost;
}

long long incrementalCost(int node, int newServer) {
    long long deltaCost = 0;
    for (const auto &edge : edges) {
        if (find(edge.members.begin(), edge.members.end(), node) != edge.members.end()) {
            set<int> servers;
            for (long long member : edge.members) {
                if (member == node) {
                    servers.insert(newServer);
                } else {
                    servers.insert(assignments[member]);
                }
            }
            deltaCost += pow(servers.size() - 1, 2);
        }
    }
    return deltaCost;
}

void optimizedFM(long long numServers, vector<int> &serverCapacities) {
    auto start_time = chrono::steady_clock::now();
    const int TIME_LIMIT = 5400; 

    while (1) {
        auto current_time = chrono::steady_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();
        if (elapsed_time >= TIME_LIMIT) {
            cout << "Time limit reached, stopping optimization.\n";
            break;
        }

        for (int i = 0; i < nodes.size(); ++i) {
            int currentServer = assignments[i];
            for (int s = 0; s < numServers; ++s) {
                if (s == currentServer) continue;
                if (serverCapacities[s] < nodes[i].weight) continue;

                long long deltaCost = incrementalCost(i, s) - incrementalCost(i, currentServer);
                if (deltaCost < 0) {  
                    assignments[i] = s;
                    serverCapacities[s] -= nodes[i].weight;
                    serverCapacities[currentServer] += nodes[i].weight;
                }
            }
        }
    }
}

void build_graph(long long numServers) {

    assignments.resize(nodes.size(), 0);
    vector<int> serverCapacities(numServers, maxDiskCapacity);

    for (long long i = 0; i < edges.size(); ++i) {

        for (int j = 0; j < edges[i].members.size(); j++) {
            if (nodes[edges[i].members[j]].server != -1) {
                continue;
            }

            for (long long s = 0; s < serverCapacities.size(); ++s) {
                // cout<<edges[i].members[j]<<endl;
                // cout<<"serverCapacities["<<s<<"]: "<<serverCapacities[s]<<endl;
                // cout<<serverCapacities[s]<<endl;
                if (s == numServers - 1 && serverCapacities[s] < nodes[edges[i].members[j]].weight) {
                    numServers++;
                    serverCapacities.push_back(maxDiskCapacity);
                }
                if (serverCapacities[s] >= nodes[edges[i].members[j]].weight) {
                    // file << s << endl;
                    assignments[edges[i].members[j]] = s;
                    serverCapacities[s] -= nodes[edges[i].members[j]].weight;
                    nodes[edges[i].members[j]].server = s;
                    break;
                }
            }
        }
    }
    // optimizedFM(numServers, serverCapacities);
}

int main(int argc, char *argv[]) {
    ifstream cin(argv[0]);
    ofstream cout(argv[1]);
    string line;
    long long n, m;

    cin >> maxDiskCapacity;
    cin >> line;

    if (line == ".agent") {
        cin >> n;
        for (long long i = 0; i < n; i++) {
            Node node;
            cin >> line;
            node.weight = stoi(line);
            node.id = i;
            node.server = -1;
            nodes.push_back(node);
        }
    } else {
        cout << "Error: .agent not found" << endl;
        return 0;
    }
    cin >> line;
    if (line == ".team") {
        cin >> n;
        for (long long i = 0; i < n; i++) {
            Edge edge;
            edge.total_weight = 0;
            edge.edge_cost = 0;
            cin >> m;
            for (long long j = 0; j < m; j++) {
                cin >> line;
                edge.members.push_back(stoi(line));
                edge.total_weight += nodes[stoi(line)].weight;
            }
            edges.push_back(edge);
        }
    } else {
        cout << "Error: .team not found" << endl;
        return 0;
    }


    if (maxDiskCapacity < 500000) {
        sort(edges.begin(), edges.end(), [](Edge &a, Edge &b) {
            if (a.members.size() != b.members.size()) return a.members.size() > b.members.size();
            return a.total_weight < b.total_weight;
        });
    }

    build_graph(2);


    // output
    int numServers = 0;
    for (int i = 0; i < assignments.size(); i++) {
        if (assignments[i] > numServers) {
            numServers = assignments[i];
        }
    }
    cout << calculateCost() << endl;
    cout << numServers + 1 << endl;

    for (long long i = 0; i < assignments.size(); ++i) {
        cout << assignments[i] << endl;
    }

    return 0;
}