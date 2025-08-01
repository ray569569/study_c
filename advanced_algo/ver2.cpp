#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <cmath>

using namespace std;

// Simplified PathFinder with strict no-overlap constraint
class SimplifiedPathFinder {
    static const int MAXN = 65;
    int W, H;
    
    // Grid information
    bool blocked[MAXN][MAXN];
    int usage[MAXN][MAXN];      // Current usage count
    double history[MAXN][MAXN];  // Historical congestion cost
    
    struct Net {
        int id;
        int sx, sy, ex, ey;
        vector<pair<int,int>> path;
        bool routed = false;
        int length = 0;
        int bends = 0;
    };
    
    vector<Net> nets;
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};
    
    // PathFinder parameters
    double historyIncrement = 1.0;   // Increased for faster convergence
    double usagePenalty = 100.0;     // Heavily penalize overlaps
    
public:
    void init(int w, int h) {
        W = w; H = h;
        memset(blocked, 0, sizeof(blocked));
        memset(usage, 0, sizeof(usage));
        memset(history, 0, sizeof(history));
    }
    
    void addBlockage(int x1, int y1, int x2, int y2) {
        for (int y = y1; y <= y2; y++) {
            for (int x = x1; x <= x2; x++) {
                if (x >= 1 && x <= W && y >= 1 && y <= H) {
                    blocked[y][x] = true;
                }
            }
        }
    }
    
    void addNet(int x1, int y1, int x2, int y2) {
        Net net;
        net.id = nets.size();
        net.sx = x1; net.sy = y1;
        net.ex = x2; net.ey = y2;
        nets.push_back(net);
    }
    
    // Cost function with strict overlap penalty
    double getCost(int x, int y, bool strict = false) {
        if (blocked[y][x]) return 1e9;  // Blocked cells are infeasible
        double cost = 1.0;  // Base cost
        
        // Historical cost
        cost += history[y][x];
        
        // Strict mode: any usage makes the cell infeasible
        if (strict && usage[y][x] > 0) return 1e9;
        
        // Normal mode: penalize based on current usage
        if (usage[y][x] > 0) {
            cost *= (1.0 + usage[y][x] * usagePenalty);
        }
        
        return cost;
    }
    
    // Dijkstra with strict no-overlap option
    bool routeNet(Net& net, bool strict = false) {
        double dist[MAXN][MAXN];
        pair<int,int> parent[MAXN][MAXN];
        
        // Initialize
        for (int i = 0; i <= H; i++) {
            for (int j = 0; j <= W; j++) {
                dist[i][j] = 1e9;
                parent[i][j] = {-1, -1};
            }
        }
        
        priority_queue<pair<double, pair<int,int>>> pq;
        pq.push({0, {net.sx, net.sy}});
        dist[net.sy][net.sx] = 0;
        
        while (!pq.empty()) {
            auto [d, pos] = pq.top();
            pq.pop();
            auto [x, y] = pos;
            d = -d;
            
            if (x == net.ex && y == net.ey) {
                // Reconstruct path
                net.path.clear();
                int cx = x, cy = y;
                while (cx != -1) {
                    net.path.push_back({cx, cy});
                    auto [nx, ny] = parent[cy][cx];
                    cx = nx; cy = ny;
                }
                reverse(net.path.begin(), net.path.end());
                
                // Validate no overlaps in strict mode
                if (strict) {
                    for (auto [px, py] : net.path) {
                        if (usage[py][px] > 0) {
                            net.path.clear();
                            return false;
                        }
                    }
                }
                
                net.routed = true;
                calculateStats(net);
                return true;
            }
            
            if (d > dist[y][x] + 0.01) continue;
            
            // Explore neighbors
            for (int dir = 0; dir < 4; dir++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                
                if (nx < 1 || nx > W || ny < 1 || ny > H) continue;
                
                double moveCost = getCost(nx, ny, strict);
                if (moveCost >= 1e9) continue;
                
                double newDist = d + moveCost;
                
                if (newDist < dist[ny][nx]) {
                    dist[ny][nx] = newDist;
                    parent[ny][nx] = {x, y};
                    pq.push({-newDist, {nx, ny}});
                }
            }
        }
        
        return false;
    }
    
    void calculateStats(Net& net) {
        net.length = net.path.size() - 1;
        net.bends = 0;
        
        for (int i = 1; i < net.path.size() - 1; i++) {
            int dx1 = net.path[i].first - net.path[i-1].first;
            int dy1 = net.path[i].second - net.path[i-1].second;
            int dx2 = net.path[i+1].first - net.path[i].first;
            int dy2 = net.path[i+1].second - net.path[i].second;
            if (dx1 != dx2 || dy1 != dy2) {
                net.bends++;
            }
        }
    }
    
    void updateUsage(const Net& net, int delta) {
        for (auto [x, y] : net.path) {
            usage[y][x] += delta;
        }
    }
    
    void updateHistory() {
        for (int y = 1; y <= H; y++) {
            for (int x = 1; x <= W; x++) {
                if (usage[y][x] > 1) {
                    history[y][x] += (usage[y][x] - 1) * historyIncrement;
                }
            }
        }
    }
    
    bool hasConflicts() {
        for (int y = 1; y <= H; y++) {
            for (int x = 1; x <= W; x++) {
                if (usage[y][x] > 1) return true;
            }
        }
        return false;
    }
    
    // Validate and mark conflicted nets as failed
    void validateSolution() {
        vector<bool> conflicted(nets.size(), false);
        for (int y = 1; y <= H; y++) {
            for (int x = 1; x <= W; x++) {
                if (usage[y][x] > 1) {
                    // Mark all nets using this cell as conflicted
                    for (int i = 0; i < nets.size(); i++) {
                        if (!nets[i].routed) continue;
                        for (auto [px, py] : nets[i].path) {
                            if (px == x && py == y) {
                                conflicted[i] = true;
                                break;
                            }
                        }
                    }
                }
            }
        }
        
        // Clear conflicted nets
        for (int i = 0; i < nets.size(); i++) {
            if (conflicted[i] && nets[i].routed) {
                updateUsage(nets[i], -1);
                nets[i].routed = false;
                nets[i].path.clear();
                nets[i].length = 0;
                nets[i].bends = 0;
            }
        }
    }
    
    void solve() {
        auto startTime = chrono::high_resolution_clock::now();
        
        cout << "=== Simplified PathFinder Router ===" << endl;
        cout << "Nets: " << nets.size() << ", Grid: " << W << "x" << H << endl;
        
        // Step 1: Sort nets by Manhattan distance
        sort(nets.begin(), nets.end(), [](const Net& a, const Net& b) {
            int distA = abs(a.ex - a.sx) + abs(a.ey - a.sy);
            int distB = abs(b.ex - b.sx) + abs(b.ey - b.sy);
            return distA < distB;
        });
        
        // Step 2: Initial routing with strict no-overlap
        cout << "\nPhase 1: Initial routing (no overlaps)" << endl;
        for (auto& net : nets) {
            if (routeNet(net, true)) {
                updateUsage(net, 1);
            }
        }
        
        int routed = 0;
        for (const auto& net : nets) {
            if (net.routed) routed++;
        }
        cout << "Initial: " << routed << "/" << nets.size() << " routed" << endl;
        
        // Step 3: PathFinder negotiation for remaining nets
        cout << "\nPhase 2: PathFinder negotiation" << endl;
        int iteration = 0;
        const int MAX_ITER = 50;
        
        while (iteration < MAX_ITER) {
            iteration++;
            
            // Update historical costs
            updateHistory();
            
            // Find unrouted nets
            vector<int> unroutedNets;
            for (int i = 0; i < nets.size(); i++) {
                if (!nets[i].routed) {
                    unroutedNets.push_back(i);
                }
            }
            
            // Sort by potential difficulty (e.g., Manhattan distance)
            sort(unroutedNets.begin(), unroutedNets.end(), [&](int a, int b) {
                int distA = abs(nets[a].ex - nets[a].sx) + abs(nets[a].ey - nets[a].sy);
                int distB = abs(nets[b].ex - nets[b].sx) + abs(nets[b].ey - nets[b].sy);
                return distA > distB;  // Prioritize longer nets
            });
            
            // Try routing unrouted nets
            int newlyRouted = 0;
            for (int idx : unroutedNets) {
                if (routeNet(nets[idx], true)) {
                    updateUsage(nets[idx], 1);
                    newlyRouted++;
                }
            }
            
            // Dynamic parameter adjustment
            if (iteration % 10 == 0) {
                historyIncrement *= 1.2;  // Escalate faster
            }
            
            // Progress report
            if (iteration % 5 == 0 || newlyRouted > 0) {
                routed = 0;
                for (const auto& net : nets) {
                    if (net.routed) routed++;
                }
                cout << "Iter " << iteration << ": " << routed << "/" << nets.size() 
                     << " routed" << endl;
            }
            
            // Time check
            auto currentTime = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
            if (elapsed > 900) {  // 15 minutes
                cout << "Time limit approaching, stopping iteration..." << endl;
                break;
            }
            
            if (unroutedNets.empty()) break;
        }
        
        // Step 4: Validate solution to ensure no conflicts
        cout << "\nPhase 3: Final validation" << endl;
        validateSolution();
        
        // Restore original net order
        sort(nets.begin(), nets.end(), [](const Net& a, const Net& b) {
            return a.id < b.id;
        });
        
        // Final statistics
        routed = 0;
        for (const auto& net : nets) {
            if (net.routed) routed++;
        }
        
        auto endTime = chrono::high_resolution_clock::now();
        auto totalTime = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
        
        cout << "\n=== Final Result ===" << endl;
        cout << "Routed: " << routed << "/" << nets.size() << endl;
        cout << "Success rate: " << (100.0 * routed / nets.size()) << "%" << endl;
        cout << "Total time: " << totalTime << " seconds" << endl;
    }
    
    void writeOutput(const string& filename) {
        ofstream out(filename);
        
        int routed = 0, totalLen = 0, totalBends = 0;
        int longest = -1, maxLen = 0;
        
        for (int i = 0; i < nets.size(); i++) {
            if (nets[i].routed) {
                routed++;
                totalLen += nets[i].length;
                totalBends += nets[i].bends;
                if (nets[i].length > maxLen) {
                    maxLen = nets[i].length;
                    longest = i;
                }
            }
        }
        
        out << "#interconnections routed = " << routed << endl;
        out << "Total interconnection length = " << totalLen << endl;
        if (longest >= 0) {
            out << "The longest interconnection = " << (longest + 1) 
                << "; length = " << maxLen << endl;
        }
        out << "Total number of bends = " << totalBends << endl;
        
        for (int i = 0; i < nets.size(); i++) {
            if (nets[i].routed) {
                out << "Interconnection " << (i + 1) << ": length = " 
                    << nets[i].length << ", #bends = " << nets[i].bends << endl;
                
                bool first = true;
                for (auto [x, y] : nets[i].path) {
                    if (!first) out << ", ";
                    out << "(" << x << ", " << y << ")";
                    first = false;
                }
                out << endl;
            } else {
                out << "Interconnection " << (i + 1) << ": fails." << endl;
            }
        }
        
        out.close();
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    
    ifstream in(argv[1]);
    if (!in) {
        cerr << "Error opening input file" << endl;
        return 1;
    }
    
    int W, H;
    in >> W >> H;
    
    SimplifiedPathFinder router;
    router.init(W, H);
    
    string line;
    getline(in, line);
    getline(in, line);
    int nBlocks = stoi(line.substr(11));
    
    for (int i = 0; i < nBlocks; i++) {
        int x1, y1, x2, y2;
        in >> x1 >> y1 >> x2 >> y2;
        router.addBlockage(x1, y1, x2, y2);
    }
    
    getline(in, line);
    getline(in, line);
    int nNets = stoi(line.substr(18));
    
    for (int i = 0; i < nNets; i++) {
        int x1, y1, x2, y2;
        in >> x1 >> y1 >> x2 >> y2;
        router.addNet(x1, y1, x2, y2);
    }
    
    in.close();
    
    router.solve();
    router.writeOutput(argv[2]);
    
    return 0;
}