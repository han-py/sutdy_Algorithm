#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

static const int INF = 1e9;

// =========================================================
// 1. 邻接矩阵版：关键路径（Critical Path）
// =========================================================
class CriticalPathMatrix {
private:
    int n;
    vector<vector<int>> mat;

public:
    CriticalPathMatrix(int n) : n(n), mat(n, vector<int>(n, INF)) {}

    void addEdge(int u, int v, int w) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "边索引越界，无法添加：" << u << " -> " << v << "（权值：" << w << "）" << endl;
            return;
        }
        mat[u][v] = w;
    }

    void printGraph() const {
        cout << "\n【邻接矩阵图结构】" << endl;
        for (int i = 0; i < n; ++i) {
            bool hasEdge = false;
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] != INF) {
                    hasEdge = true;
                    cout << i << " -> " << j << " (duration=" << mat[i][j] << ")\t";
                }
            }
            if (hasEdge) cout << endl;
        }
    }

    vector<int> topoSortKahn() const {
        vector<int> indeg(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] != INF) {
                    ++indeg[j];
                }
            }
        }

        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indeg[i] == 0) q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (int v = 0; v < n; ++v) {
                if (mat[u][v] != INF) {
                    --indeg[v];
                    if (indeg[v] == 0) q.push(v);
                }
            }
        }

        return topo;
    }

    void computeCriticalPath() {
        cout << "\n==================== 邻接矩阵版关键路径 ====================" << endl;
        printGraph();

        vector<int> topo = topoSortKahn();
        if (topo.size() != static_cast<size_t>(n)) {
            cout << "图中存在环，不能计算关键路径。" << endl;
            return;
        }

        cout << "拓扑序：";
        for (int x : topo) cout << x << " ";
        cout << endl;

        // 1）最早发生时间 earliest[i]
        vector<int> earliest(n, 0);
        for (int u : topo) {
            for (int v = 0; v < n; ++v) {
                if (mat[u][v] != INF) {
                    earliest[v] = max(earliest[v], earliest[u] + mat[u][v]);
                }
            }
        }

        // 2）最晚发生时间 latest[i]
        vector<int> latest(n, earliest[n - 1]);
        for (int i = (int)topo.size() - 1; i >= 0; --i) {
            int u = topo[i];
            for (int v = 0; v < n; ++v) {
                if (mat[u][v] != INF) {
                    latest[u] = min(latest[u], latest[v] - mat[u][v]);
                }
            }
        }

        cout << "\n各顶点的最早开始时间（earliest）：" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "  v" << i << " = " << earliest[i] << endl;
        }

        cout << "\n各顶点的最晚开始时间（latest）：" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "  v" << i << " = " << latest[i] << endl;
        }

        vector<pair<int, int>> criticalEdges;
        cout << "\n关键路径判定：松弛量 = latest[v] - earliest[u] - weight(u,v)" << endl;
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (mat[u][v] != INF) {
                    int slack = latest[v] - earliest[u] - mat[u][v];
                    cout << "  边 " << u << " -> " << v << "：slack = " << slack;
                    if (slack == 0) {
                        cout << "  （关键边）";
                        criticalEdges.emplace_back(u, v);
                    }
                    cout << endl;
                }
            }
        }

        cout << "\n关键路径边：";
        if (criticalEdges.empty()) {
            cout << "无" << endl;
        } else {
            for (size_t i = 0; i < criticalEdges.size(); ++i) {
                if (i) cout << " -> ";
                auto [u, v] = criticalEdges[i];
                cout << u << "->" << v;
            }
            cout << endl;
        }

        cout << "完成时间（项目工期） = " << earliest[n - 1] << endl;
        cout << "===============================================" << endl;
    }
};

// =========================================================
// 2. 邻接表版：关键路径（Critical Path）
// =========================================================
class CriticalPathList {
private:
    int n;
    vector<vector<pair<int, int>>> graph;

public:
    CriticalPathList(int n) : n(n), graph(n) {}

    void addEdge(int u, int v, int w) {
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "边索引越界，无法添加：" << u << " -> " << v << "（权值：" << w << "）" << endl;
            return;
        }
        graph[u].push_back({v, w});
    }

    void printGraph() const {
        cout << "\n【邻接表图结构】" << endl;
        for (int i = 0; i < n; ++i) {
            if (!graph[i].empty()) {
                cout << "顶点 " << i << "：";
                for (auto [v, w] : graph[i]) {
                    cout << " -> " << v << "(w=" << w << ")";
                }
                cout << endl;
            }
        }
    }

    vector<int> topoSortKahn() const {
        vector<int> indeg(n, 0);
        for (int u = 0; u < n; ++u) {
            for (auto [v, w] : graph[u]) {
                ++indeg[v];
            }
        }

        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indeg[i] == 0) q.push(i);
        }

        vector<int> topo;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            for (auto [v, w] : graph[u]) {
                --indeg[v];
                if (indeg[v] == 0) q.push(v);
            }
        }

        return topo;
    }

    void computeCriticalPath() {
        cout << "\n==================== 邻接表版关键路径 ====================" << endl;
        printGraph();

        vector<int> topo = topoSortKahn();
        if (topo.size() != static_cast<size_t>(n)) {
            cout << "图中存在环，不能计算关键路径。" << endl;
            return;
        }

        cout << "拓扑序：";
        for (int x : topo) cout << x << " ";
        cout << endl;

        vector<int> earliest(n, 0);
        for (int u : topo) {
            for (auto [v, w] : graph[u]) {
                earliest[v] = max(earliest[v], earliest[u] + w);
            }
        }

        vector<int> latest(n, earliest[n - 1]);
        for (int i = (int)topo.size() - 1; i >= 0; --i) {
            int u = topo[i];
            for (auto [v, w] : graph[u]) {
                latest[u] = min(latest[u], latest[v] - w);
            }
        }

        cout << "\n各顶点的最早开始时间（earliest）：" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "  v" << i << " = " << earliest[i] << endl;
        }

        cout << "\n各顶点的最晚开始时间（latest）：" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "  v" << i << " = " << latest[i] << endl;
        }

        vector<pair<int, int>> criticalEdges;
        cout << "\n关键路径判定：松弛量 = latest[v] - earliest[u] - weight(u,v)" << endl;
        for (int u = 0; u < n; ++u) {
            for (auto [v, w] : graph[u]) {
                int slack = latest[v] - earliest[u] - w;
                cout << "  边 " << u << " -> " << v << "：slack = " << slack;
                if (slack == 0) {
                    cout << "  （关键边）";
                    criticalEdges.emplace_back(u, v);
                }
                cout << endl;
            }
        }

        cout << "\n关键路径边：";
        if (criticalEdges.empty()) {
            cout << "无" << endl;
        } else {
            for (size_t i = 0; i < criticalEdges.size(); ++i) {
                if (i) cout << " -> ";
                auto [u, v] = criticalEdges[i];
                cout << u << "->" << v;
            }
            cout << endl;
        }

        cout << "完成时间（项目工期） = " << earliest[n - 1] << endl;
        cout << "===============================================" << endl;
    }
};

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif

    cout << "=====================================================" << endl;
    cout << "关键路径（Critical Path）学习示例" << endl;
    cout << "本例采用 AOE 网络（Activity On Edge）模型" << endl;
    cout << "顶点表示事件，边表示活动，边权表示活动持续时间" << endl;
    cout << "=====================================================" << endl;

    // 例子：7 个顶点（0..6），表示一个工程网络
    // 关键路径应为：0 -> 2 -> 3 -> 6
    int n = 7;

    CriticalPathMatrix matrixGraph(n);
    matrixGraph.addEdge(0, 1, 3);
    matrixGraph.addEdge(0, 2, 4);
    matrixGraph.addEdge(1, 3, 5);
    matrixGraph.addEdge(1, 4, 6);
    matrixGraph.addEdge(2, 3, 8);
    matrixGraph.addEdge(2, 5, 7);
    matrixGraph.addEdge(3, 4, 3);
    matrixGraph.addEdge(3, 6, 9);
    matrixGraph.addEdge(4, 6, 4);
    matrixGraph.addEdge(5, 6, 2);
    matrixGraph.computeCriticalPath();

    CriticalPathList listGraph(n);
    listGraph.addEdge(0, 1, 3);
    listGraph.addEdge(0, 2, 4);
    listGraph.addEdge(1, 3, 5);
    listGraph.addEdge(1, 4, 6);
    listGraph.addEdge(2, 3, 8);
    listGraph.addEdge(2, 5, 7);
    listGraph.addEdge(3, 4, 3);
    listGraph.addEdge(3, 6, 9);
    listGraph.addEdge(4, 6, 4);
    listGraph.addEdge(5, 6, 2);
    listGraph.computeCriticalPath();

    cout << "\n=====================================================" << endl;
    cout << "总结：" << endl;
    cout << "关键路径是工程网络中总工期最长的路径。" << endl;
    cout << "所有关键边的 slack 都为 0，表示它们不能延迟。" << endl;
    cout << "关键路径 = 0 -> 2 -> 3 -> 6，持续时间 = 21" << endl;
    cout << "=====================================================" << endl;

    return 0;
}
