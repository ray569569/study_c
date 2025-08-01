#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <chrono>

const int MAX_SIZE = 64;
const int MAX_NETS = 30;
const int MAX_BLOCKAGES = 40;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& p) const { return x == p.x && y == p.y; }
};

struct Node {
    Point pos;
    int detour;
    int distance;
    
    bool operator>(const Node& other) const {
        if (detour != other.detour) return detour > other.detour;
        return distance > other.distance;
    }
};

struct RoutingResult {
    bool success;
    std::vector<Point> path;
    int length;
    int bends;
};

class MazeRouter {
private:
    int width, height;
    std::bitset<MAX_SIZE * MAX_SIZE> obstacles;
    std::bitset<MAX_SIZE * MAX_SIZE> occupied;
    std::vector<float> congestionHistory;
    
    const int dx[4] = {1, 0, -1, 0};
    const int dy[4] = {0, 1, 0, -1};
    
    std::chrono::high_resolution_clock::time_point startTime;
    const int TIME_LIMIT_SECONDS = 1200; // 20 minutes
    
public:
    MazeRouter(int w, int h) : width(w), height(h) {
        congestionHistory.resize(width * height, 1.0f);
        startTime = std::chrono::high_resolution_clock::now();
    }
    
    inline int getIndex(int x, int y) const {
        return y * width + x;
    }
    
    inline bool isValid(int x, int y) const {
        return x >= 1 && x <= width && y >= 1 && y <= height;
    }
    
    void addBlockage(int x1, int y1, int x2, int y2) {
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                if (isValid(x, y)) {
                    obstacles[getIndex(x-1, y-1)] = true;
                }
            }
        }
    }
    
    std::vector<Point> routeNet(const Point& start, const Point& target) {
        std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
        std::vector<int> visited(width * height, -1);
        std::vector<Point> parent(width * height);
        
        // Adjust coordinates to 0-indexed
        Point s(start.x - 1, start.y - 1);
        Point t(target.x - 1, target.y - 1);
        
        Node startNode = {s, 0, 0};
        pq.push(startNode);
        visited[getIndex(s.x, s.y)] = 0;
        
        while (!pq.empty()) {
            // Check time limit
            if (checkTimeLimit()) {
                return std::vector<Point>();
            }
            
            Node current = pq.top();
            pq.pop();
            
            if (current.pos == t) {
                return reconstructPath(parent, s, t, start);
            }
            
            for (int dir = 0; dir < 4; dir++) {
                int nx = current.pos.x + dx[dir];
                int ny = current.pos.y + dy[dir];
                
                if (!isValid(nx + 1, ny + 1)) continue;
                
                int nidx = getIndex(nx, ny);
                
                if (obstacles[nidx] || occupied[nidx]) continue;
                
                int newDetour = calculateDetour(current, dir, t);
                
                if (visited[nidx] == -1 || visited[nidx] > newDetour) {
                    visited[nidx] = newDetour;
                    parent[nidx] = current.pos;
                    
                    Node newNode = {Point(nx, ny), newDetour, current.distance + 1};
                    pq.push(newNode);
                }
            }
        }
        
        return std::vector<Point>();
    }
    
    std::vector<RoutingResult> routeAllNets(const std::vector<std::pair<Point, Point>>& nets) {
        std::vector<RoutingResult> results(nets.size());
        std::vector<int> netOrder = orderNets(nets);
        
        for (int idx : netOrder) {
            auto& net = nets[idx];
            std::vector<Point> path = routeNet(net.first, net.second);
            
            results[idx].success = !path.empty();
            
            if (results[idx].success) {
                results[idx].path = path;
                results[idx].length = path.size() - 1;
                results[idx].bends = countBends(path);
                
                for (const Point& p : path) {
                    occupied[getIndex(p.x - 1, p.y - 1)] = true;
                }
            }
        }
        
        // Try rip-up and reroute for failed nets
        improveRouting(results, nets);
        
        return results;
    }
    
private:
    int calculateDetour(const Node& current, int direction, const Point& target) {
        int nx = current.pos.x + dx[direction];
        int ny = current.pos.y + dy[direction];
        
        bool towardTarget = false;
        if ((dx[direction] != 0 && dx[direction] == sgn(target.x - current.pos.x)) ||
            (dy[direction] != 0 && dy[direction] == sgn(target.y - current.pos.y))) {
            towardTarget = true;
        }
        
        return towardTarget ? current.detour : current.detour + 1;
    }
    
    int sgn(int val) {
        return (val > 0) - (val < 0);
    }
    
    std::vector<Point> reconstructPath(const std::vector<Point>& parent,
                                     const Point& start, const Point& target,
                                     const Point& origStart) {
        std::vector<Point> path;
        Point current = target;
        
        while (!(current == start)) {
            // Convert back to 1-indexed
            path.push_back(Point(current.x + 1, current.y + 1));
            int idx = getIndex(current.x, current.y);
            current = parent[idx];
        }
        path.push_back(origStart);
        
        std::reverse(path.begin(), path.end());
        return path;
    }
    
    int countBends(const std::vector<Point>& path) {
        if (path.size() < 3) return 0;
        
        int bends = 0;
        for (size_t i = 1; i < path.size() - 1; i++) {
            int dx1 = path[i].x - path[i-1].x;
            int dy1 = path[i].y - path[i-1].y;
            int dx2 = path[i+1].x - path[i].x;
            int dy2 = path[i+1].y - path[i].y;
            
            if (dx1 != dx2 || dy1 != dy2) {
                bends++;
            }
        }
        return bends;
    }
    
    struct NetInfo {
        int index;
        int length;
        int boundingBox;
        float congestion;
    };
    
    std::vector<int> orderNets(const std::vector<std::pair<Point, Point>>& nets) {
        std::vector<NetInfo> netInfos;
        
        for (size_t i = 0; i < nets.size(); i++) {
            NetInfo info;
            info.index = i;
            
            const Point& s = nets[i].first;
            const Point& t = nets[i].second;
            
            info.length = abs(t.x - s.x) + abs(t.y - s.y);
            info.boundingBox = abs(t.x - s.x) * abs(t.y - s.y);
            info.congestion = estimateCongestion(s, t);
            
            netInfos.push_back(info);
        }
        
        std::sort(netInfos.begin(), netInfos.end(), 
            [](const NetInfo& a, const NetInfo& b) {
                if (abs(a.length - b.length) > 5) {
                    return a.length > b.length;
                }
                return a.congestion < b.congestion;
            });
        
        std::vector<int> order;
        for (const auto& info : netInfos) {
            order.push_back(info.index);
        }
        return order;
    }
    
    float estimateCongestion(const Point& s, const Point& t) {
        int x1 = std::min(s.x, t.x) - 1;
        int y1 = std::min(s.y, t.y) - 1;
        int x2 = std::max(s.x, t.x) - 1;
        int y2 = std::max(s.y, t.y) - 1;
        
        int obstacleCount = 0;
        int totalCells = 0;
        
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                if (isValid(x + 1, y + 1)) {
                    totalCells++;
                    if (obstacles[getIndex(x, y)]) {
                        obstacleCount++;
                    }
                }
            }
        }
        
        return totalCells > 0 ? (float)obstacleCount / totalCells : 0.0f;
    }
    
    void improveRouting(std::vector<RoutingResult>& results,
                       const std::vector<std::pair<Point, Point>>& nets) {
        const int MAX_ITERATIONS = 3;
        
        for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
            std::vector<int> failedNets;
            for (size_t i = 0; i < results.size(); i++) {
                if (!results[i].success) {
                    failedNets.push_back(i);
                }
            }
            
            if (failedNets.empty()) break;
            
            // Try to reroute failed nets
            for (int netIdx : failedNets) {
                if (checkTimeLimit()) return;
                
                auto path = routeNet(nets[netIdx].first, nets[netIdx].second);
                if (!path.empty()) {
                    results[netIdx].success = true;
                    results[netIdx].path = path;
                    results[netIdx].length = path.size() - 1;
                    results[netIdx].bends = countBends(path);
                    
                    for (const Point& p : path) {
                        occupied[getIndex(p.x - 1, p.y - 1)] = true;
                    }
                }
            }
        }
    }
    
    bool checkTimeLimit() {
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
        return elapsed > TIME_LIMIT_SECONDS - 10; // Leave 10 seconds margin
    }
};

void outputResults(const std::vector<RoutingResult>& results) {
    int routedCount = 0;
    int totalLength = 0;
    int totalBends = 0;
    int maxLength = 0;
    int maxLengthNet = -1;
    
    for (size_t i = 0; i < results.size(); i++) {
        if (results[i].success) {
            routedCount++;
            totalLength += results[i].length;
            totalBends += results[i].bends;
            
            if (results[i].length > maxLength) {
                maxLength = results[i].length;
                maxLengthNet = i + 1;
            }
        }
    }
    
    std::cout << "#interconnections routed = " << routedCount << "\n";
    std::cout << "Total interconnection length = " << totalLength << "\n";
    std::cout << "The longest interconnection = " << maxLengthNet 
              << "; length = " << maxLength << "\n";
    std::cout << "Total number of bends = " << totalBends << "\n";
    
    for (size_t i = 0; i < results.size(); i++) {
        if (results[i].success) {
            std::cout << "Interconnection " << (i + 1) 
                     << ": length = " << results[i].length
                     << ", #bends = " << results[i].bends << "\n";
            
            for (size_t j = 0; j < results[i].path.size(); j++) {
                if (j > 0) std::cout << ", ";
                std::cout << "(" << results[i].path[j].x 
                         << ", " << results[i].path[j].y << ")";
            }
            std::cout << "\n";
        } else {
            std::cout << "Interconnection " << (i + 1) << ": fails.\n";
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>\n";
        return 1;
    }
    
    std::ifstream input(argv[1]);
    std::ofstream output(argv[2]);
    
    // Redirect cout to output file
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    
    int w, h;
    input >> w >> h;
    
    MazeRouter router(w, h);
    
    // Read blockages
    std::string line;
    input >> line >> line; // Skip "#blockages n"
    int numBlockages = std::stoi(line);
    
    for (int i = 0; i < numBlockages; i++) {
        int x1, y1, x2, y2;
        input >> x1 >> y1 >> x2 >> y2;
        router.addBlockage(x1, y1, x2, y2);
    }
    
    // Read nets
    input >> line >> line; // Skip "#interconnections m"
    int numNets = std::stoi(line);
    
    std::vector<std::pair<Point, Point>> nets;
    for (int i = 0; i < numNets; i++) {
        int x1, y1, x2, y2;
        input >> x1 >> y1 >> x2 >> y2;
        nets.push_back({Point(x1, y1), Point(x2, y2)});
    }
    
    // Route all nets
    auto results = router.routeAllNets(nets);
    
    // Output results
    outputResults(results);
    
    // Restore cout
    std::cout.rdbuf(coutbuf);
    
    return 0;
}