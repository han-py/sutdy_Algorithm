#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

/*
  dfs_learning.cpp
  用途: 学习图的深度优先搜索(DFS)的示例程序。
  本文件包含：
    1) 邻接矩阵表示的图（Adjacency Matrix）
       - 递归版 DFS
       - 迭代（栈）版 DFS
    2) 邻接表表示的图（Adjacency List）
       - 递归版 DFS
       - 迭代（栈）版 DFS
    3) 记录访问顺序、父节点、发现时间与完成时间（递归版）
    4) 示例图与自动演示（程序运行时会输出示例结果）

  注释与输出均为中文，用于学习和教学。
*/

// ---------- 通用辅助打印函数（中文提示） ----------
void printDivider() {
    cout << "------------------------------------------------------------\n";
}

// ---------- 邻接矩阵表示的图 ----------
struct GraphMatrix {
    int n; // 节点数，节点编号从 0 到 n-1
    vector<vector<int>> mat; // n x n 的邻接矩阵，0/1 表示是否有边（适合无权图）

    GraphMatrix(int n = 0) : n(n), mat(n, vector<int>(n, 0)) {}

    void addEdge(int u, int v, bool undirected = true) {
        if (u < 0 || u >= n || v < 0 || v >= n) return;
        mat[u][v] = 1;
        if (undirected) mat[v][u] = 1;
    }

    // 递归版 DFS：记录发现时间与完成时间
    void dfsRecursive(int start = 0) {
        vector<int> visited(n, 0); // 0 未访问，1 访问中，2 已完成
        vector<int> parent(n, -1);
        vector<int> discover(n, -1), finish(n, -1);
        vector<int> order; // 记录访问顺序（入栈/发现顺序）
        int time = 0;

        function<void(int)> dfs = [&](int u) {
            visited[u] = 1;
            discover[u] = ++time; // 记录发现时间
            order.push_back(u);
            // 输出当前正在访问的节点（中文提示）
            cout << "矩阵-递归: 发现节点 " << u << " (discover=" << discover[u] << ")\n";
            for (int v = 0; v < n; ++v) {
                if (mat[u][v]) {
                    if (!visited[v]) {
                        parent[v] = u;
                        cout << "  矩阵-递归: 从 " << u << " 递归到 " << v << "\n";
                        dfs(v);
                    } else {
                        // 可以在此处输出遇到已访问节点的信息（用于理解回边/横向边）
                        // 注意：若 visited[v]==1 表示遇到回边（到正在访问的祖先）
                        if (visited[v] == 1) {
                            cout << "  矩阵-递归: 遇到回边 " << u << "->" << v << " (v 正在访问中)\n";
                        } else {
                            cout << "  矩阵-递归: 遇到横/前向边 " << u << "->" << v << " (v 已完成)\n";
                        }
                    }
                }
            }
            visited[u] = 2;
            finish[u] = ++time;
            cout << "矩阵-递归: 完成节点 " << u << " (finish=" << finish[u] << ")\n";
        };

        cout << "开始矩阵-递归 DFS，从节点 " << start << " 开始\n";
        dfs(start);

        // 若图不连通，这里继续从未访问的节点开始
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                cout << "矩阵-递归: 图不连通，从未访问节点 " << i << " 继续 DFS\n";
                dfs(i);
            }
        }

        // 打印总结信息
        printDivider();
        cout << "矩阵-递归 DFS 完成。访问顺序(发现顺序)：";
        for (int u : order) cout << u << " ";
        cout << "\n父节点数组(parent)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << parent[i] << "\n";
        cout << "发现时间 discover：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << discover[i] << "\n";
        cout << "完成时间 finish：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << finish[i] << "\n";
    }

    // 迭代版 DFS（使用显式栈），记录访问顺序
    void dfsIterative(int start = 0) {
        vector<int> visited(n, 0);
        vector<int> parent(n, -1);
        vector<int> order;

        cout << "开始矩阵-迭代 DFS，从节点 " << start << " 开始\n";
        stack<int> st;
        st.push(start);

        while (!st.empty()) {
            int u = st.top(); st.pop();
            if (visited[u]) continue;
            visited[u] = 1;
            order.push_back(u);
            cout << "矩阵-迭代: 访问节点 " << u << "\n";
            // 注意：为了让访问顺序和递归版更相似，这里逆序遍历邻居（因为栈是 LIFO）
            for (int v = n-1; v >= 0; --v) {
                if (mat[u][v] && !visited[v]) {
                    parent[v] = u;
                    cout << "  矩阵-迭代: 将邻居 " << v << " 入栈（父=" << u << "）\n";
                    st.push(v);
                }
            }
        }

        // 若图不连通，继续从未访问节点开始
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                cout << "矩阵-迭代: 图不连通，从未访问节点 " << i << " 继续 DFS\n";
                st.push(i);
                while (!st.empty()) {
                    int u = st.top(); st.pop();
                    if (visited[u]) continue;
                    visited[u] = 1;
                    order.push_back(u);
                    cout << "矩阵-迭代: 访问节点 " << u << "\n";
                    for (int v = n-1; v >= 0; --v) {
                        if (mat[u][v] && !visited[v]) {
                            parent[v] = u;
                            cout << "  矩阵-迭代: 将邻居 " << v << " 入栈（父=" << u << "）\n";
                            st.push(v);
                        }
                    }
                }
            }
        }

        printDivider();
        cout << "矩阵-迭代 DFS 完成。访问顺序：";
        for (int u : order) cout << u << " ";
        cout << "\n父节点数组(parent)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << parent[i] << "\n";
    }
};

// ---------- 邻接表表示的图 ----------
struct GraphList {
    int n;
    vector<vector<int>> adj; // 邻接表：adj[u] 包含 u 的所有邻居

    GraphList(int n = 0) : n(n), adj(n) {}

    void addEdge(int u, int v, bool undirected = true) {
        if (u < 0 || u >= n || v < 0 || v >= n) return;
        adj[u].push_back(v);
        if (undirected) adj[v].push_back(u);
    }

    // 递归版 DFS，带发现/完成时间
    void dfsRecursive(int start = 0) {
        vector<int> visited(n, 0);
        vector<int> parent(n, -1);
        vector<int> discover(n, -1), finish(n, -1);
        vector<int> order;
        int time = 0;

        // 为了让递归访问顺序与邻接矩阵示例类似，先对邻居排序（升序）
        for (int u = 0; u < n; ++u) sort(adj[u].begin(), adj[u].end());

        function<void(int)> dfs = [&](int u) {
            visited[u] = 1;
            discover[u] = ++time;
            order.push_back(u);
            cout << "表-递归: 发现节点 " << u << " (discover=" << discover[u] << ")\n";
            for (int v : adj[u]) {
                if (!visited[v]) {
                    parent[v] = u;
                    cout << "  表-递归: 从 " << u << " 递归到 " << v << "\n";
                    dfs(v);
                } else {
                    if (visited[v] == 1) cout << "  表-递归: 遇到回边 " << u << "->" << v << "\n";
                    else cout << "  表-递归: 遇到横/前向边 " << u << "->" << v << "\n";
                }
            }
            visited[u] = 2;
            finish[u] = ++time;
            cout << "表-递归: 完成节点 " << u << " (finish=" << finish[u] << ")\n";
        };

        cout << "开始邻接表-递归 DFS，从节点 " << start << " 开始\n";
        dfs(start);
        for (int i = 0; i < n; ++i) if (!visited[i]) {
            cout << "表-递归: 图不连通，从未访问节点 " << i << " 继续 DFS\n";
            dfs(i);
        }

        printDivider();
        cout << "表-递归 DFS 完成。访问顺序(发现顺序)：";
        for (int u : order) cout << u << " ";
        cout << "\n父节点数组(parent)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << parent[i] << "\n";
        cout << "发现时间 discover：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << discover[i] << "\n";
        cout << "完成时间 finish：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << finish[i] << "\n";
    }

    // 迭代版 DFS（栈）
    void dfsIterative(int start = 0) {
        vector<int> visited(n, 0);
        vector<int> parent(n, -1);
        vector<int> order;

        // 为了让栈遍历结果和递归版更相似，对邻居进行降序入栈
        for (int u = 0; u < n; ++u) sort(adj[u].begin(), adj[u].end());

        cout << "开始邻接表-迭代 DFS，从节点 " << start << " 开始\n";
        stack<int> st;
        st.push(start);
        while (!st.empty()) {
            int u = st.top(); st.pop();
            if (visited[u]) continue;
            visited[u] = 1;
            order.push_back(u);
            cout << "表-迭代: 访问节点 " << u << "\n";
            // 逆序遍历邻居以使得小编号先被处理（更接近递归顺序）
            for (int i = (int)adj[u].size()-1; i >= 0; --i) {
                int v = adj[u][i];
                if (!visited[v]) {
                    parent[v] = u;
                    cout << "  表-迭代: 将邻居 " << v << " 入栈（父=" << u << "）\n";
                    st.push(v);
                }
            }
        }

        for (int i = 0; i < n; ++i) if (!visited[i]) {
            cout << "表-迭代: 图不连通，从未访问节点 " << i << " 继续 DFS\n";
            st.push(i);
            while (!st.empty()) {
                int u = st.top(); st.pop();
                if (visited[u]) continue;
                visited[u] = 1;
                order.push_back(u);
                cout << "表-迭代: 访问节点 " << u << "\n";
                for (int j = (int)adj[u].size()-1; j >= 0; --j) {
                    int v = adj[u][j];
                    if (!visited[v]) {
                        parent[v] = u;
                        cout << "  表-迭代: 将邻居 " << v << " 入栈（父=" << u << "）\n";
                        st.push(v);
                    }
                }
            }
        }

        printDivider();
        cout << "表-迭代 DFS 完成。访问顺序：";
        for (int u : order) cout << u << " ";
        cout << "\n父节点数组(parent)：\n";
        for (int i = 0; i < n; ++i) cout << i << ": " << parent[i] << "\n";
    }
};

// ---------- 示例图生成函数 ----------
// 例子：一个包含回边和多个连通分量的小图，便于观察 DFS 行为
void buildSampleGraphs(GraphMatrix &gm, GraphList &gl) {
    // 假设 n=7，节点 0..6
    // 边集合（无向图示例）：
    // 0-1, 0-2, 1-3, 1-4, 2-5, 5-6, 3-4 (额外的边产生回边/环)
    // 同时保留一个孤立点（例如没有额外孤立点，这里都连通）
    vector<pair<int,int>> edges = {
        {0,1}, {0,2}, {1,3}, {1,4}, {2,5}, {5,6}, {3,4}
    };
    for (auto &e : edges) {
        gm.addEdge(e.first, e.second, true);
        gl.addEdge(e.first, e.second, true);
    }
}

// 主函数：自动演示四种实现的运行结果
int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "图的深度优先搜索(DFS) 学习示例程序\n";
    printDivider();
    cout << "程序说明（中文）:\n";
    cout << "  - 演示邻接矩阵与邻接表两种图表示的 DFS。\n";
    cout << "  - 每种表示分别给出递归和迭代（使用显式栈）实现，程序会输出详细的访问过程与父节点/时间信息。\n";
    printDivider();

    int n = 7;
    GraphMatrix gm(n);
    GraphList gl(n);
    buildSampleGraphs(gm, gl);

    cout << "示例图: 共 " << n << " 个节点 (编号 0.." << n-1 << ")。边集合示例已构建。\n";
    printDivider();

    // 矩阵递归
    gm.dfsRecursive(0);

    // 矩阵迭代
    printDivider();
    gm.dfsIterative(0);

    // 邻接表递归
    printDivider();
    gl.dfsRecursive(0);

    // 邻接表迭代
    printDivider();
    gl.dfsIterative(0);

    printDivider();
    cout << "演示结束。\n";
    cout << "提示：若想学习不同的图或从控制台输入图数据，可修改 main() 中的示例或扩展本程序以从标准输入读取。\n";
    return 0;
}


