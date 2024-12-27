#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <cmath>
#include <algorithm>

using namespace std;

// 节点与边定义
class Node {
public:
    int id;
    int weight; // 内存需求

};

class Edge {
public:
    vector<int> members; // 边连接的节点集合
    int weight;          // 通信成本（默认为1）
};

// 全局变量
int maxDiskCapacity;
vector<Node> nodes;
vector<Edge> edges;
vector<int> assignments; // 节点分配的服务器ID

// 计算通信成本
int calculateCost() {
    int totalCost = 0;
    unordered_map<int, set<int>> teamServers;

    for (const auto& edge : edges) {
        set<int> servers;
        for (int member : edge.members) {
            servers.insert(assignments[member]);
        }
        totalCost += pow(servers.size() - 1, 2);
    }
    return totalCost;
}

// Fiduccia-Mattheyses (FM) 划分算法
void fiducciaMattheyses(int numServers) {
    // 初始划分：将节点随机分配到服务器
    assignments.resize(nodes.size(), 0);
    vector<int> serverCapacities(numServers, maxDiskCapacity);

    for (int i = 0; i < nodes.size(); ++i) {
        for (int s = 0; s < numServers; ++s) {
            if (serverCapacities[s] >= nodes[i].weight) {
                assignments[i] = s;
                serverCapacities[s] -= nodes[i].weight;
                break;
            }
        }
    }

    // 优化：尝试移动节点减少通信成本
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < nodes.size(); ++i) {
            int currentServer = assignments[i];
            for (int s = 0; s < numServers; ++s) {
                if (s == currentServer) continue;

                // 试探性移动节点
                assignments[i] = s;
                int newCost = calculateCost();
                if (newCost < calculateCost()) {
                    improved = true; // 成本降低，保留移动
                    break;
                } else {
                    assignments[i] = currentServer; // 恢复
                }
            }
        }
    }
}

int main() {
    // 初始化输入，构建图
    // 运行 FM 算法或其他方法
    fiducciaMattheyses(2); // 示例：2-way 划分
    cout << "Total Cost: " << calculateCost() << endl;

    return 0;
}
