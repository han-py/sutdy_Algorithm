#include <algorithm>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

namespace {

constexpr int INF = 1'000'000'000;

string vertex_name(const vector<char>& vertices, int index) {
    return index >= 0 && index < static_cast<int>(vertices.size())
               ? string(1, vertices[index])
               : string("?");
}

string index_or_empty(int index) {
    return index == -1 ? string("∅") : to_string(index);
}

string weight_or_inf(int weight) {
    return weight >= INF / 2 ? string("∞") : to_string(weight);
}

string join_vertices(const vector<char>& vertices, const vector<int>& order) {
    if (order.empty()) {
        return "(空)";
    }
    ostringstream oss;
    for (size_t i = 0; i < order.size(); ++i) {
        if (i) {
            oss << " -> ";
        }
        oss << vertices[order[i]];
    }
    return oss.str();
}

void print_banner(const string& title) {
    cout << "\n============================================================\n";
    cout << title << '\n';
    cout << "============================================================\n";
}

void print_subtitle(const string& subtitle) {
    cout << "\n【" << subtitle << "】\n";
}

template <typename NeighborGetter>
vector<int> dfs_order(int start, int n, NeighborGetter getter) {
    vector<int> order;
    vector<bool> visited(n, false);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        order.push_back(u);
        vector<int> neighbors = getter(u);
        sort(neighbors.begin(), neighbors.end());
        for (int v : neighbors) {
            if (!visited[v]) {
                dfs(v);
            }
        }
    };
    dfs(start);
    return order;
}

template <typename NeighborGetter>
vector<int> bfs_order(int start, int n, NeighborGetter getter) {
    vector<int> order;
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        vector<int> neighbors = getter(u);
        sort(neighbors.begin(), neighbors.end());
        for (int v : neighbors) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return order;
}

template <typename NeighborGetter>
void trace_dfs_impl(int u, int depth, vector<bool>& visited, const vector<char>& vertices,
                    NeighborGetter getter) {
    visited[u] = true;
    cout << string(depth * 2, ' ') << "访问顶点 " << vertices[u] << "，并标记为已访问。\n";

    vector<int> neighbors = getter(u);
    sort(neighbors.begin(), neighbors.end());
    for (int v : neighbors) {
        if (!visited[v]) {
            cout << string(depth * 2, ' ') << "从 " << vertices[u] << " 递归访问邻接点 " << vertices[v]
                 << "。\n";
            trace_dfs_impl(v, depth + 1, visited, vertices, getter);
        } else {
            cout << string(depth * 2, ' ') << "顶点 " << vertices[v] << " 已访问，跳过。\n";
        }
    }

    cout << string(depth * 2, ' ') << "顶点 " << vertices[u] << " 的邻接点处理完毕，开始回溯。\n";
}

template <typename NeighborGetter>
void trace_dfs(int start, int n, const vector<char>& vertices, NeighborGetter getter,
               const string& title) {
    print_subtitle(title);
    vector<bool> visited(n, false);
    trace_dfs_impl(start, 0, visited, vertices, getter);
}

template <typename NeighborGetter>
void trace_bfs(int start, int n, const vector<char>& vertices, NeighborGetter getter,
               const string& title) {
    print_subtitle(title);
    vector<bool> visited(n, false);
    deque<int> q;
    visited[start] = true;
    q.push_back(start);
    cout << "初始状态：队列中只有 " << vertices[start] << "。\n";

    while (!q.empty()) {
        cout << "当前队列：";
        for (int x : q) {
            cout << ' ' << vertices[x];
        }
        cout << "\n";

        int u = q.front();
        q.pop_front();
        cout << "出队顶点 " << vertices[u] << "，开始检查它的邻接点。\n";

        vector<int> neighbors = getter(u);
        sort(neighbors.begin(), neighbors.end());
        for (int v : neighbors) {
            if (!visited[v]) {
                visited[v] = true;
                q.push_back(v);
                cout << "  发现未访问顶点 " << vertices[v] << "，入队。\n";
            } else {
                cout << "  顶点 " << vertices[v] << " 已访问，忽略。\n";
            }
        }
    }
}

struct MatrixGraph {
    vector<char> vertices;
    vector<vector<int>> matrix;
    bool directed = false;
};

struct ListGraph {
    vector<char> vertices;
    vector<vector<pair<int, int>>> adj;
    bool directed = false;
};

struct MultiListGraph {
    struct EdgeBox {
        int ivex = -1;
        int jvex = -1;
        int ilink = -1;
        int jlink = -1;
        int weight = 1;
    };

    struct VertexNode {
        char data = '?';
        int firstedge = -1;
    };

    vector<VertexNode> vertices;
    vector<EdgeBox> edges;
};

struct OrthogonalGraph {
    struct ArcBox {
        int tailvex = -1;
        int headvex = -1;
        int tlink = -1;
        int hlink = -1;
        int weight = 1;
    };

    struct VertexNode {
        char data = '?';
        int firstin = -1;
        int firstout = -1;
    };

    vector<VertexNode> vertices;
    vector<ArcBox> arcs;
};

MatrixGraph build_matrix_graph(const vector<char>& vertices,
                               const vector<tuple<int, int, int>>& edges,
                               bool directed) {
    MatrixGraph g;
    g.vertices = vertices;
    g.directed = directed;
    int n = static_cast<int>(vertices.size());
    g.matrix.assign(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        g.matrix[i][i] = 0;
    }

    for (const auto& [u, v, w] : edges) {
        g.matrix[u][v] = min(g.matrix[u][v], w);
        if (!directed) {
            g.matrix[v][u] = min(g.matrix[v][u], w);
        }
    }
    return g;
}

ListGraph build_list_graph(const vector<char>& vertices, const vector<tuple<int, int, int>>& edges,
                           bool directed) {
    ListGraph g;
    g.vertices = vertices;
    g.directed = directed;
    int n = static_cast<int>(vertices.size());
    g.adj.assign(n, {});
    for (const auto& [u, v, w] : edges) {
        g.adj[u].push_back({v, w});
        if (!directed) {
            g.adj[v].push_back({u, w});
        }
    }
    return g;
}

MultiListGraph build_multi_list_graph(const vector<char>& vertices,
                                      const vector<tuple<int, int, int>>& edges) {
    MultiListGraph g;
    g.vertices.reserve(vertices.size());
    for (char c : vertices) {
        g.vertices.push_back({c, -1});
    }

    for (const auto& [u, v, w] : edges) {
        int index = static_cast<int>(g.edges.size());
        g.edges.push_back({u, v, g.vertices[u].firstedge, g.vertices[v].firstedge, w});
        g.vertices[u].firstedge = index;
        g.vertices[v].firstedge = index;
    }
    return g;
}

OrthogonalGraph build_orthogonal_graph(const vector<char>& vertices,
                                       const vector<tuple<int, int, int>>& edges) {
    OrthogonalGraph g;
    g.vertices.reserve(vertices.size());
    for (char c : vertices) {
        g.vertices.push_back({c, -1, -1});
    }

    for (const auto& [tail, head, w] : edges) {
        int index = static_cast<int>(g.arcs.size());
        g.arcs.push_back({tail, head, g.vertices[tail].firstout, g.vertices[head].firstin, w});
        g.vertices[tail].firstout = index;
        g.vertices[head].firstin = index;
    }
    return g;
}

vector<int> matrix_neighbors(const MatrixGraph& g, int u) {
    vector<int> neighbors;
    for (int v = 0; v < static_cast<int>(g.vertices.size()); ++v) {
        if (u != v && g.matrix[u][v] < INF / 2) {
            neighbors.push_back(v);
        }
    }
    return neighbors;
}

vector<int> list_neighbors(const ListGraph& g, int u) {
    vector<int> neighbors;
    for (const auto& [v, w] : g.adj[u]) {
        (void)w;
        neighbors.push_back(v);
    }
    return neighbors;
}

vector<int> multilist_neighbors(const MultiListGraph& g, int u) {
    vector<int> neighbors;
    for (int e = g.vertices[u].firstedge; e != -1;) {
        const auto& edge = g.edges[e];
        int v = (edge.ivex == u) ? edge.jvex : edge.ivex;
        neighbors.push_back(v);
        e = (edge.ivex == u) ? edge.ilink : edge.jlink;
    }
    return neighbors;
}

vector<int> orthogonal_neighbors(const OrthogonalGraph& g, int u) {
    vector<int> neighbors;
    for (int a = g.vertices[u].firstout; a != -1; a = g.arcs[a].tlink) {
        neighbors.push_back(g.arcs[a].headvex);
    }
    return neighbors;
}

void print_applicability_table() {
    print_subtitle("图片中的适用性总表");
    cout << left << setw(18) << "图的类型"
         << setw(18) << "邻接矩阵"
         << setw(18) << "邻接表"
         << setw(18) << "邻接多重表"
         << setw(18) << "十字链表" << '\n';
    cout << string(90, '-') << '\n';
    cout << left << setw(18) << "有向图" << setw(18) << "√" << setw(18) << "√" << setw(18) << "×"
         << setw(18) << "√" << '\n';
    cout << left << setw(18) << "无向图" << setw(18) << "√" << setw(18) << "√" << setw(18) << "√"
         << setw(18) << "×" << '\n';
}

void print_matrix_graph(const MatrixGraph& g, const string& title) {
    print_subtitle(title + (g.directed ? "（有向图）" : "（无向图）"));
    cout << "顶点序号：";
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << ' ' << g.vertices[i] << '(' << i << ')';
    }
    cout << '\n';

    cout << setw(6) << " ";
    for (char c : g.vertices) {
        cout << setw(6) << c;
    }
    cout << '\n';

    for (size_t i = 0; i < g.matrix.size(); ++i) {
        cout << setw(6) << g.vertices[i];
        for (size_t j = 0; j < g.matrix[i].size(); ++j) {
            cout << setw(6) << weight_or_inf(g.matrix[i][j]);
        }
        cout << '\n';
    }
}

void print_list_graph(const ListGraph& g, const string& title) {
    print_subtitle(title + (g.directed ? "（有向图）" : "（无向图）"));
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << g.vertices[i] << " -> ";
        if (g.adj[i].empty()) {
            cout << "∅";
        } else {
            for (size_t k = 0; k < g.adj[i].size(); ++k) {
                const auto& [v, w] = g.adj[i][k];
                cout << g.vertices[v] << '(' << w << ')';
                if (k + 1 != g.adj[i].size()) {
                    cout << " -> ";
                }
            }
        }
        cout << '\n';
    }
}

void print_multi_list_graph(const MultiListGraph& g, const string& title) {
    print_subtitle(title + "（无向图）");
    cout << "顶点表：\n";
    cout << left << setw(8) << "序号" << setw(8) << "顶点" << setw(10) << "firstedge" << '\n';
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << left << setw(8) << i << setw(8) << g.vertices[i].data << setw(10)
             << index_or_empty(g.vertices[i].firstedge) << '\n';
    }

    cout << "边表：\n";
    cout << left << setw(8) << "序号" << setw(10) << "边" << setw(10) << "权值" << setw(10)
         << "ilink" << setw(10) << "jlink" << '\n';
    for (size_t i = 0; i < g.edges.size(); ++i) {
        const auto& e = g.edges[i];
        cout << left << setw(8) << i << setw(10)
             << (string(1, g.vertices[e.ivex].data) + "-" + string(1, g.vertices[e.jvex].data))
             << setw(10) << e.weight << setw(10) << index_or_empty(e.ilink) << setw(10)
             << index_or_empty(e.jlink) << '\n';
    }

    cout << "按顶点展开后的邻接关系：\n";
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << g.vertices[i].data << " : ";
        vector<int> neighbors = multilist_neighbors(g, static_cast<int>(i));
        if (neighbors.empty()) {
            cout << "∅";
        } else {
            for (size_t k = 0; k < neighbors.size(); ++k) {
                cout << g.vertices[neighbors[k]].data;
                if (k + 1 != neighbors.size()) {
                    cout << " -> ";
                }
            }
        }
        cout << '\n';
    }
}

void print_orthogonal_graph(const OrthogonalGraph& g, const string& title) {
    print_subtitle(title + "（有向图）");
    cout << "顶点表：\n";
    cout << left << setw(8) << "序号" << setw(8) << "顶点" << setw(10) << "firstout"
         << setw(10) << "firstin" << '\n';
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << left << setw(8) << i << setw(8) << g.vertices[i].data << setw(10)
             << index_or_empty(g.vertices[i].firstout) << setw(10)
             << index_or_empty(g.vertices[i].firstin) << '\n';
    }

    cout << "弧表：\n";
    cout << left << setw(8) << "序号" << setw(10) << "弧" << setw(10) << "权值" << setw(10)
         << "tlink" << setw(10) << "hlink" << '\n';
    for (size_t i = 0; i < g.arcs.size(); ++i) {
        const auto& a = g.arcs[i];
        cout << left << setw(8) << i << setw(10)
             << (string(1, g.vertices[a.tailvex].data) + "→" + string(1, g.vertices[a.headvex].data))
             << setw(10) << a.weight << setw(10) << index_or_empty(a.tlink) << setw(10)
             << index_or_empty(a.hlink) << '\n';
    }

    cout << "按顶点展开后的出边：\n";
    for (size_t i = 0; i < g.vertices.size(); ++i) {
        cout << g.vertices[i].data << " : ";
        vector<int> neighbors = orthogonal_neighbors(g, static_cast<int>(i));
        if (neighbors.empty()) {
            cout << "∅";
        } else {
            for (size_t k = 0; k < neighbors.size(); ++k) {
                cout << g.vertices[neighbors[k]].data;
                if (k + 1 != neighbors.size()) {
                    cout << " -> ";
                }
            }
        }
        cout << '\n';
    }
}

void print_traversal_summary(const vector<char>& vertices, const vector<int>& dfs,
                             const vector<int>& bfs) {
    cout << "DFS 访问序列：" << join_vertices(vertices, dfs) << '\n';
    cout << "BFS 访问序列：" << join_vertices(vertices, bfs) << '\n';
}

}  // namespace

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cerr << "[调试] 进入 main" << endl;
    return 0;

    vector<char> undirected_vertices = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<tuple<int, int, int>> undirected_edges = {
        {0, 1, 1}, {0, 2, 2}, {1, 3, 3}, {1, 4, 4}, {2, 5, 5}, {4, 5, 6}};

    vector<char> directed_vertices = {'A', 'B', 'C', 'D', 'E', 'F'};
    vector<tuple<int, int, int>> directed_edges = {
        {0, 1, 1}, {0, 2, 1}, {1, 3, 1}, {2, 3, 1}, {3, 4, 1}, {4, 5, 1}, {5, 2, 1}};

    auto undirected_matrix = build_matrix_graph(undirected_vertices, undirected_edges, false);
    auto undirected_list = build_list_graph(undirected_vertices, undirected_edges, false);
    auto multilist = build_multi_list_graph(undirected_vertices, undirected_edges);

    auto directed_matrix = build_matrix_graph(directed_vertices, directed_edges, true);
    auto directed_list = build_list_graph(directed_vertices, directed_edges, true);
    auto orthogonal = build_orthogonal_graph(directed_vertices, directed_edges);

    cerr << "[调试] 图结构构建完成" << endl;

    print_banner("图的结构与遍历学习程序");
    cout << "本程序覆盖：邻接矩阵、邻接表、邻接多重表、十字链表，以及 DFS / BFS 遍历。\n";
    cout << "所有注释与输出均为中文，便于直接配合课本和图片学习。\n";

    print_applicability_table();

    cerr << "[调试] 适用性表输出完成" << endl;

    print_banner("一、无向图示例：邻接矩阵 + 邻接表 + 邻接多重表");
    print_matrix_graph(undirected_matrix, "无向图的邻接矩阵");
    print_list_graph(undirected_list, "无向图的邻接表");
    print_multi_list_graph(multilist, "无向图的邻接多重表");

    cerr << "[调试] 无向图结构输出完成" << endl;

    print_banner("二、有向图示例：邻接矩阵 + 邻接表 + 十字链表");
    print_matrix_graph(directed_matrix, "有向图的邻接矩阵");
    print_list_graph(directed_list, "有向图的邻接表");
    print_orthogonal_graph(orthogonal, "有向图的十字链表");

    cerr << "[调试] 有向图结构输出完成" << endl;

    print_banner("三、遍历演示：只要能枚举邻接点，四种存储结构都能支持 DFS / BFS");
    cout << "这里统一从顶点 A 开始，演示不同结构下的遍历接口。\n";

    auto undirected_matrix_dfs = dfs_order(0, static_cast<int>(undirected_vertices.size()),
                                           [&](int u) { return matrix_neighbors(undirected_matrix, u); });
    auto undirected_matrix_bfs = bfs_order(0, static_cast<int>(undirected_vertices.size()),
                                           [&](int u) { return matrix_neighbors(undirected_matrix, u); });
    print_subtitle("无向图 - 邻接矩阵遍历结果");
    print_traversal_summary(undirected_vertices, undirected_matrix_dfs, undirected_matrix_bfs);
    trace_dfs(0, static_cast<int>(undirected_vertices.size()), undirected_vertices,
              [&](int u) { return matrix_neighbors(undirected_matrix, u); },
              "无向图 - 邻接矩阵 DFS 过程");
    trace_bfs(0, static_cast<int>(undirected_vertices.size()), undirected_vertices,
              [&](int u) { return matrix_neighbors(undirected_matrix, u); },
              "无向图 - 邻接矩阵 BFS 过程");

    auto undirected_list_dfs = dfs_order(0, static_cast<int>(undirected_vertices.size()),
                                          [&](int u) { return list_neighbors(undirected_list, u); });
    auto undirected_list_bfs = bfs_order(0, static_cast<int>(undirected_vertices.size()),
                                          [&](int u) { return list_neighbors(undirected_list, u); });
    print_subtitle("无向图 - 邻接表遍历结果");
    print_traversal_summary(undirected_vertices, undirected_list_dfs, undirected_list_bfs);

    auto multilist_dfs = dfs_order(0, static_cast<int>(undirected_vertices.size()),
                                   [&](int u) { return multilist_neighbors(multilist, u); });
    auto multilist_bfs = bfs_order(0, static_cast<int>(undirected_vertices.size()),
                                   [&](int u) { return multilist_neighbors(multilist, u); });
    print_subtitle("无向图 - 邻接多重表遍历结果");
    print_traversal_summary(undirected_vertices, multilist_dfs, multilist_bfs);

    auto directed_matrix_dfs = dfs_order(0, static_cast<int>(directed_vertices.size()),
                                          [&](int u) { return matrix_neighbors(directed_matrix, u); });
    auto directed_matrix_bfs = bfs_order(0, static_cast<int>(directed_vertices.size()),
                                          [&](int u) { return matrix_neighbors(directed_matrix, u); });
    print_subtitle("有向图 - 邻接矩阵遍历结果");
    print_traversal_summary(directed_vertices, directed_matrix_dfs, directed_matrix_bfs);

    auto directed_list_dfs = dfs_order(0, static_cast<int>(directed_vertices.size()),
                                       [&](int u) { return list_neighbors(directed_list, u); });
    auto directed_list_bfs = bfs_order(0, static_cast<int>(directed_vertices.size()),
                                       [&](int u) { return list_neighbors(directed_list, u); });
    print_subtitle("有向图 - 邻接表遍历结果");
    print_traversal_summary(directed_vertices, directed_list_dfs, directed_list_bfs);

    auto orthogonal_dfs = dfs_order(0, static_cast<int>(directed_vertices.size()),
                                     [&](int u) { return orthogonal_neighbors(orthogonal, u); });
    auto orthogonal_bfs = bfs_order(0, static_cast<int>(directed_vertices.size()),
                                     [&](int u) { return orthogonal_neighbors(orthogonal, u); });
    print_subtitle("有向图 - 十字链表遍历结果");
    print_traversal_summary(directed_vertices, orthogonal_dfs, orthogonal_bfs);
    trace_dfs(0, static_cast<int>(directed_vertices.size()), directed_vertices,
              [&](int u) { return orthogonal_neighbors(orthogonal, u); },
              "有向图 - 十字链表 DFS 过程");
    trace_bfs(0, static_cast<int>(directed_vertices.size()), directed_vertices,
              [&](int u) { return orthogonal_neighbors(orthogonal, u); },
              "有向图 - 十字链表 BFS 过程");

    cerr << "[调试] 遍历演示输出完成" << endl;

    print_banner("四、学习建议");
    cout << "1. 邻接矩阵：适合判断边是否存在，空间开销与顶点数平方成正比。\n";
    cout << "2. 邻接表：适合稀疏图，遍历邻接点更高效。\n";
    cout << "3. 邻接多重表：专门服务无向图，一条边只存一份，但能同时连接两个顶点。\n";
    cout << "4. 十字链表：专门服务有向图，既能顺着出边找，也能沿入边回溯。\n";
    cout << "5. DFS 与 BFS 的核心不是具体存储结构，而是“能否快速枚举邻接点”。\n";
    cout << "6. 这也是为什么图片中邻接矩阵、邻接表、邻接多重表、十字链表各有适用场景。\n";

    cout << "\n程序执行完毕。你可以配合 HTML 动画页面逐步学习。\n";
    cerr << "[调试] main 正常结束" << endl;
    return 0;
}




