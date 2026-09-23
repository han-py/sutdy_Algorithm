# 最小生成树（Minimum Spanning Tree）学习示例

本目录包含一个自包含的 C++ 学习示例，用于理解图的最小生成树（MST）算法。程序同时给出以下四种实现：

- Prim 算法 + 邻接矩阵
- Prim 算法 + 邻接表
- Kruskal 算法 + 邻接矩阵
- Kruskal 算法 + 邻接表

所有注释、输出提示和说明均为中文，方便用于学习和课堂讲解。

## 1. 算法概念速览

### 1.1 Prim 算法
- 适合：密集图，特别适合邻接矩阵
- 思路：从一个起点开始，持续扩展“已加入 MST 的顶点集合”，每次选取连接到集合中且代价最小的边
- 典型复杂度：
  - 邻接矩阵：O(n^2)
  - 邻接表：O(E log V)（若用堆优化）

### 1.2 Kruskal 算法
- 适合：稀疏图，特别适合邻接表
- 思路：将所有边按权值升序排序，再依次加入边；如果两端点不属于同一连通分量，则加入 MST
- 核心结构：并查集（Union-Find）
- 典型复杂度：O(E log E)

## 2. 本程序内容

`minimum_spanning_tree_learning.cpp` 包含：

- `GraphMatrix`：邻接矩阵表示法
  - `primMatrix()`
  - `kruskalMatrix()`
- `GraphList`：邻接表表示法
  - `primList()`
  - `kruskalList()`
- `DisjointSet`：并查集，用于 Kruskal
- `main()`：构造示例图并依次运行全部算法

## 3. 示例图说明

程序中构造了一个无向加权连通图，边如下：

- 0 - 1 : 4
- 0 - 2 : 6
- 0 - 3 : 1
- 1 - 2 : 2
- 1 - 4 : 5
- 2 - 3 : 3
- 2 - 4 : 4
- 3 - 4 : 2
- 3 - 5 : 5
- 4 - 5 : 1

这个图的最小生成树总权值为：

- 0 - 3 : 1
- 2 - 1 : 2
- 3 - 2 : 3
- 3 - 4 : 2
- 4 - 5 : 1

总和 = 9

## 4. 编译与运行

PowerShell 示例：

```powershell
chcp 65001

g++ -std=c++17 -O2 -Wall .\WangDao_2027\04_Graph\06_MinimumSpanningTree\minimum_spanning_tree_learning.cpp -o .\WangDao_2027\04_Graph\06_MinimumSpanningTree\minimum_spanning_tree_learning.exe

.\WangDao_2027\04_Graph\06_MinimumSpanningTree\minimum_spanning_tree_learning.exe
```

## 5. 运行过程中的输出含义

程序会输出：

- 邻接矩阵 / 邻接表的图结构
- Prim 每轮选中顶点的过程
- lowcost 更新过程
- Kruskal 按边权排序后的候选边
- 并查集合并过程
- 最终 MST 边集与总权值

## 6. 学习建议

- 先看 Prim：思路直观，适合起步
- 再看 Kruskal：强调“边排序 + 并查集”，非常适合工程和竞赛场景
- 最后比较两者：
  - 如果图比较稠：Prim / 邻接矩阵更自然
  - 如果图比较稀：Kruskal / 邻接表更高效

## 7. 扩展方向

如果你愿意，我还可以继续为你补充：

- `MST` 的图形化示意（ASCII 或注释版）
- `Prim` 堆优化版（优先队列）
- `Kruskal` 的“边排序 + 并查集”代码细节动画版
- 从 stdin 读取图并执行任意一种 MST 算法的交互版

