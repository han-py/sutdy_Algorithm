# 最短路径学习示例

本目录包含一个自包含的 C++ 示例程序 `shortest_path_learning.cpp`，用于学习图的最短路径算法：

- 无权最短路径（BFS）：邻接矩阵与邻接表实现
- 带权最短路径（Dijkstra）：邻接矩阵（O(n^2)）与邻接表（优先队列）实现
- Bellman-Ford（邻接表）：用于含负权边并检测负环

所有注释与输出均为中文，程序会构造示例图并依次演示各算法的执行过程，包含松弛步骤、入队/出队等详细输出，便于教学。

编译运行（PowerShell）：

```powershell
chcp 65001
g++ -std=c++17 -O2 -Wall .\WangDao_2027\04_Graph\05_ShortestPath\shortest_path_learning.cpp -o .\WangDao_2027\04_Graph\05_ShortestPath\shortest_path_learning.exe
.\WangDao_2027\04_Graph\05_ShortestPath\shortest_path_learning.exe
```

说明：Windows 控制台可能需要设置为 UTF-8（`chcp 65001`）并使用支持中文的字体以正确显示中文输出。

如果你希望：
- 程序改为从标准输入读取图（并选择邻接表/矩阵与算法），或
- 增加更多示例（如有向带权图最短路、Johnson 算法、用于稀疏图的优化等），

请回复我会继续实现。

