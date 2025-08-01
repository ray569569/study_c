#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#include <chrono>
#include <cmath>
#include <random>

using namespace std;

// Enhanced PathFinder with improved conflict negotiation
class EnhancedPathFinder {
    static const int MAXN = 65;
    int W, H;
    
    // Grid information
    bool blocked[MAXN][MAXN];
    int usage[MAXN][MAXN];
    double history[MAXN][MAXN];
    
    struct Net {
        int id;
        int sx, sy, ex, ey;
        vector<pair<int,int>> path;
        bool routed = false;
        int length = 0;
        int bends = 0;
        int rerouteCount = 0;
        int freedom = 0;
    };
    
    vector<Net> nets;
    const int dx[4] = {0, 1, 0, -1};
    const int dy[4] = {1, 0, -1, 0};
    
    // Parameters
    double historyIncrement = 1.0;
    double usagePenalty = 50.0;  // Reduced for more flexibility
    
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
        net.freedom = estimateFreedom(x1, y1, x2, y2);
        nets.push_back(net);
    }
    
    // Estimate routing freedom
    int estimateFreedom(int x1, int y1, int x2, int y2) {
        int freeCells = 0;
        for (int y = max(1, y1 - 2); y <= min(H, y1 + 2); y++) {
            for (int x = max(1, x1 - 2); x <= min(W, x1 + 2); x++) {
                if (!blocked[y][x] && usage[y][x] == 0) freeCells++;
            }
        }
        for (int y = max(1, y2 - 2); y <= min(H, y2 + 2); y++) {
            for (int x = max(1, x2 - 2); x <= min(W, x2 + 2); x++) {
                if (!blocked[y][x] && usage[y][x] == 0) freeCells++;
            }
        }
        return freeCells;
    }
    
    // Update freedom for all nets
    void updateFreedom() {
        for (auto& net : nets) {
            net.freedom = estimateFreedom(net.sx, net.sy, net.ex, net.ey);
        }
    }
    
    // Cost function
    double getCost(int x, int y, bool strict = false) {
        if (blocked[y][x]) return 1e9;
        double cost = 1.0;
        cost += history[y][x];
        if (strict && usage[y][x] > 0) return 1e9;
        if (usage[y][x] > 0) {
            cost *= (1.0 + usage[y][x] * usagePenalty);
        }
        return cost;
    }
    
    // Dijkstra routing
    bool routeNet(Net& net, bool strict = false) {
        double dist[MAXN][MAXN];
        pair<int,int> parent[MAXN][MAXN];
        
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
                net.path.clear();
                int cx = x, cy = y;
                while (cx != -1) {
                    net.path.push_back({cx, cy});
                    auto [nx, ny] = parent[cy][cx];
                    cx = nx; cy = ny;
                }
                reverse(net.path.begin(), net.path.end());
                
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
                net.rerouteCount++;
                return true;
            }
            
            if (d > dist[y][x] + 0.01) continue;
            
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
    
    // Compute conflict score
    int computeConflictScore(const Net& net) {
        int score = 0;
        for (auto [x, y] : net.path) {
            if (usage[y][x] > 1) score += usage[y][x] - 1;
        }
        return score;
    }
    
    // Evaluate reroute score
    double evaluateRerouteScore(const Net& net, int iteration) {
        double conflictWeight = 2.0 + 0.1 * iteration;  // Increase over iterations
        double lengthWeight = 0.05;
        double freedomWeight = 0.5;
        double bendsWeight = 0.2;
        double rerouteWeight = 1.0;
        
        int conflictScore = computeConflictScore(net);
        return conflictWeight * conflictScore +
               lengthWeight * net.length -
               freedomWeight * net.freedom +
               bendsWeight * net.bends +
               rerouteWeight * net.rerouteCount;
    }
    
    // Negotiate conflicts
    bool negotiateConflicts(int newNetIdx, int iteration) {
        vector<pair<int, double>> conflictNets;  // (net index, reroute score)
        vector<int> conflictingIndices;
        
        // Collect all nets involved in conflicts
        for (int y = 1; y <= H; y++) {
            for (int x = 1; x <= W; x++) {
                if (usage[y][x] <= 1) continue;
                for (int i = 0; i < nets.size(); i++) {
                    if (!nets[i].routed) continue;
                    for (auto [px, py] : nets[i].path) {
                        if (px == x && py == y) {
                            conflictingIndices.push_back(i);
                            break;
                        }
                    }
                }
            }
        }
        
        // Include new net if applicable
        if (newNetIdx >= 0 && nets[newNetIdx].routed) {
            conflictingIndices.push_back(newNetIdx);
        }
        
        if (conflictingIndices.empty()) return false;
        
        // Remove duplicates
        sort(conflictingIndices.begin(), conflictingIndices.end());
        conflictingIndices.erase(unique(conflictingIndices.begin(), conflictingIndices.end()), conflictingIndices.end());
        
        // Compute reroute scores
        for (int idx : conflictingIndices) {
            double score = evaluateRerouteScore(nets[idx], iteration);
            conflictNets.push_back({idx, score});
            cout << "Net " << (nets[idx].id + 1) << ": conflict score = " << computeConflictScore(nets[idx])
                 << ", length = " << nets[idx].length << ", freedom = " << nets[idx].freedom
                 << ", bends = " << nets[idx].bends << ", reroutes = " << nets[idx].rerouteCount
                 << ", total score = " << score << endl;
        }
        
        // Sort by reroute score (highest score gets rerouted)
        sort(conflictNets.begin(), conflictNets.end(), 
             [](const auto& a, const auto& b) { return a.second > b.second; });
        
        // Reroute the net with the highest score
        int rerouteIdx = conflictNets[0].first;
        cout << "Rerouting Net " << (nets[rerouteIdx].id + 1) << endl;
        updateUsage(nets[rerouteIdx], -1);
        nets[rerouteIdx].routed = false;
        nets[rerouteIdx].path.clear();
        nets[rerouteIdx].length = 0;
        nets[rerouteIdx].bends = 0;
        
        return true;
    }
    
    void solve() {
        auto startTime = chrono::high_resolution_clock::now();
        
        cout << "=== Enhanced PathFinder Router ===" << endl;
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
        
        // Step 3: PathFinder negotiation with conflict resolution
        cout << "\nPhase 2: PathFinder negotiation" << endl;
        int iteration = 0;
        const int MAX_ITER = 50;
        int lastRouted = routed;
        int stagnantCount = 0;  // Track iterations with no progress
        
        random_device rd;
        mt19937 g(rd());
        
        while (iteration < MAX_ITER) {
            iteration++;
            
            // Update historical costs
            updateHistory();
            
            // Update freedom
            updateFreedom();
            
            // Find unrouted nets
            vector<int> unroutedNets;
            for (int i = 0; i < nets.size(); i++) {
                if (!nets[i].routed) {
                    unroutedNets.push_back(i);
                }
            }
            
            // Shuffle unrouted nets for randomization
            shuffle(unroutedNets.begin(), unroutedNets.end(), g);
            
            // Try routing unrouted nets
            int newlyRouted = 0;
            for (int idx : unroutedNets) {
                if (routeNet(nets[idx], false)) {
                    updateUsage(nets[idx], 1);
                    if (hasConflicts()) {
                        cout << "Conflict detected after routing Net " << (nets[idx].id + 1) << endl;
                        negotiateConflicts(idx, iteration);
                    }
                    if (nets[idx].routed) newlyRouted++;
                }
            }
            
            // Resolve remaining conflicts
            while (hasConflicts()) {
                cout << "Resolving remaining conflicts in iteration " << iteration << endl;
                negotiateConflicts(-1, iteration);
            }
            
            // Dynamic parameter adjustment
            if (iteration % 3 == 0) {
                historyIncrement *= 1.3;
            }
            
            // Progress report
            routed = 0;
            for (const auto& net : nets) {
                if (net.routed) routed++;
            }
            if (iteration % 5 == 0 || newlyRouted > 0) {
                cout << "Iter " << iteration << ": " << routed << "/" << nets.size() 
                     << " routed" << endl;
            }
            
            // Early termination with leniency
            if (routed == lastRouted && newlyRouted == 0) {
                stagnantCount++;
                if (stagnantCount >= 10) {  // Allow 10 stagnant iterations
                    cout << "No progress after " << stagnantCount << " iterations, stopping early..." << endl;
                    break;
                }
            } else {
                stagnantCount = 0;
            }
            lastRouted = routed;
            
            // Time check
            auto currentTime = chrono::high_resolution_clock::now();
            auto elapsed = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
            if (elapsed > 900) {
                cout << "Time limit approaching, stopping iteration..." << endl;
                break;
            }
            
            if (unroutedNets.empty()) break;
        }
        
        // Step 4: Final conflict resolution
        cout << "\nPhase 3: Final conflict resolution" << endl;
        while (hasConflicts()) {
            negotiateConflicts(-1, iteration);
        }
        
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
    
    EnhancedPathFinder router;
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