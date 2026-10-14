cmake_minimum_required(VERSION 4.2)
project(DataStructures)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-D ACM_LOCAL)

add_executable(DataStructures
        main.cpp)
target_link_libraries(DataStructures)

add_executable(WD_04_Graph_02_DataStructureAndTraversal_GraphStorageTraversalLearning
        WangDao_2027/04_Graph/02_DataStructureAndTraversal/graph_storage_traversal_learning_simple.cpp)
target_compile_options(WD_04_Graph_02_DataStructureAndTraversal_GraphStorageTraversalLearning PRIVATE -g0)
target_link_libraries(WD_04_Graph_02_DataStructureAndTraversal_GraphStorageTraversalLearning)

add_executable(WD_02_LinkedList_02_BasicOperations_LinkedList_BasicOps
        WangDao_2027/02_LinkedList/02_BasicOperations/linked_list_basic_ops.cpp)
target_link_libraries(WD_02_LinkedList_02_BasicOperations_LinkedList_BasicOps)

add_executable(WD_01_SequentialList_02_QuickSort_02_QuickSort
        WangDao_2027/01_SequentialList/02_QuickSort/02_QuickSort.cpp)
target_compile_definitions(WD_01_SequentialList_02_QuickSort_02_QuickSort PRIVATE RUN_QIUCKSORT_WD)

add_executable(WD_01_SequentialList_04_OptimizedSolution_01_BinarySearch_template1_equivalent
        WangDao_2027/01_SequentialList/04_OptimizedSolution/01_BinarySearch/template1_equivalent.cpp)
target_compile_definitions(WD_01_SequentialList_04_OptimizedSolution_01_BinarySearch_template1_equivalent PRIVATE RUN_TEMPLATE1_EQUIVALENT_WD)

add_executable(WD_01_SequentialList_04_OptimizedSolution_01_BinarySearch_template2_interval
        WangDao_2027/01_SequentialList/04_OptimizedSolution/01_BinarySearch/template2_interval.cpp)
target_compile_definitions(WD_01_SequentialList_04_OptimizedSolution_01_BinarySearch_template2_interval PRIVATE RUN_TEMPLATE2_INTERVAL_WD)

add_executable(WD_01_SequentialList_04_OptimizedSolution_03_preprocessing_2_6_On_Kadane_Kadane
        WangDao_2027/01_SequentialList/04_OptimizedSolution/03_preprocessing/2_6_On_Kadane/Kadane.cpp)
target_compile_definitions(WD_01_SequentialList_04_OptimizedSolution_03_preprocessing_2_6_On_Kadane_Kadane PRIVATE RUN_KADANE_WD)

add_executable(WD_01_SequentialList_04_OptimizedSolution_03_preprocessing_fixed_length_max_subarray
        WangDao_2027/01_SequentialList/04_OptimizedSolution/03_preprocessing/fixed_length_max_subarray.cpp)
target_compile_definitions(WD_01_SequentialList_04_OptimizedSolution_03_preprocessing_fixed_length_max_subarray PRIVATE RUN_FIXED_LENGTH_MAX_SUBARRAY_WD)

add_executable(WD_01_SequentialList_04_OptimizedSolution_04_MultiPointerTechnique_quickselect_split_half
        WangDao_2027/01_SequentialList/04_OptimizedSolution/04_MultiPointerTechnique/quickselect_split_half.cpp)
target_compile_definitions(WD_01_SequentialList_04_OptimizedSolution_04_MultiPointerTechnique_quickselect_split_half PRIVATE RUN_MULTIPOINTERTECHNIQUE_WD)

add_executable(WD_03_Tree_02_Traverse_TreeTraversalLearning
        WangDao_2027/03_Tree/02_Traverse/tree_traversal_learning.cpp)
target_compile_options(WD_03_Tree_02_Traverse_TreeTraversalLearning PRIVATE -g0)
target_link_libraries(WD_03_Tree_02_Traverse_TreeTraversalLearning)

add_executable(WD_03_Tree_02_Traverse_TreeTraversalLearning_Compare
        WangDao_2027/03_Tree/02_Traverse/tree_traversal_learning_compare.cpp)
target_compile_options(WD_03_Tree_02_Traverse_TreeTraversalLearning_Compare PRIVATE -g0)
target_link_libraries(WD_03_Tree_02_Traverse_TreeTraversalLearning_Compare)

add_executable(WD_04_Graph_03_DepthFirstTraversal_dfs_learning
        WangDao_2027/04_Graph/03_DepthFirstTraversal/dfs_learning.cpp)
target_compile_options(WD_04_Graph_03_DepthFirstTraversal_dfs_learning PRIVATE -g0)
target_link_libraries(WD_04_Graph_03_DepthFirstTraversal_dfs_learning)

add_executable(WD_04_Graph_04_BreadthFirstSearch_bfs_learning
        WangDao_2027/04_Graph/04_BreadthFirstSearch/bfs_learning.cpp)
target_compile_options(WD_04_Graph_04_BreadthFirstSearch_bfs_learning PRIVATE -g0)
target_link_libraries(WD_04_Graph_04_BreadthFirstSearch_bfs_learning)

add_executable(WD_04_Graph_05_ShortestPath_shortest_path_learning
        WangDao_2027/04_Graph/05_ShortestPath/shortest_path_learning.cpp)
target_compile_options(WD_04_Graph_05_ShortestPath_shortest_path_learning PRIVATE -g0)
target_link_libraries(WD_04_Graph_05_ShortestPath_shortest_path_learning)

add_executable(WD_04_Graph_06_MinimumSpanningTree_minimum_spanning_tree_learning
        WangDao_2027/04_Graph/06_MinimumSpanningTree/minimum_spanning_tree_learning.cpp)
target_compile_options(WD_04_Graph_06_MinimumSpanningTree_minimum_spanning_tree_learning PRIVATE -g0)
target_link_libraries(WD_04_Graph_06_MinimumSpanningTree_minimum_spanning_tree_learning)

add_executable(WD_04_Graph_07_TopologicalSort_topological_sort_learning
        WangDao_2027/04_Graph/07_TopologicalSort/topological_sort_learning.cpp)
target_compile_options(WD_04_Graph_07_TopologicalSort_topological_sort_learning PRIVATE -g0)
target_link_libraries(WD_04_Graph_07_TopologicalSort_topological_sort_learning)

add_executable(WD_04_Graph_08_CriticalPath_critical_path_learning
        WangDao_2027/04_Graph/08_CriticalPath/critical_path_learning.cpp)
target_compile_options(WD_04_Graph_08_CriticalPath_critical_path_learning PRIVATE -g0)
target_link_libraries(WD_04_Graph_08_CriticalPath_critical_path_learning)

add_executable(Foundation_Utilities
        DataStructuresStudyPack/00_Foundation/Foundation_Utilities.cpp)

add_executable(Linear_Structures
        DataStructuresStudyPack/01_Linear_Structures/Linear_Structures.cpp)
add_executable(Linear_Array
        DataStructuresStudyPack/01_Linear_Structures/Array.cpp)
add_executable(Linear_LinkedList
        DataStructuresStudyPack/01_Linear_Structures/LinkedList.cpp)
add_executable(Linear_Stack
        DataStructuresStudyPack/01_Linear_Structures/Stack.cpp)
add_executable(Linear_Queue
        DataStructuresStudyPack/01_Linear_Structures/Queue.cpp)
add_executable(Linear_Deque
        DataStructuresStudyPack/01_Linear_Structures/Deque.cpp)
add_executable(Linear_String
        DataStructuresStudyPack/01_Linear_Structures/String.cpp)

add_executable(Tree_Structures
        DataStructuresStudyPack/02_Tree_Structures/Tree_Structures.cpp)
add_executable(Tree_BinaryTree
        DataStructuresStudyPack/02_Tree_Structures/BinaryTree.cpp)
add_executable(Tree_BinarySearchTree
        DataStructuresStudyPack/02_Tree_Structures/BinarySearchTree.cpp)
add_executable(Tree_BalancedTree
        DataStructuresStudyPack/02_Tree_Structures/BalancedTree.cpp)
add_executable(Tree_Heap_And_PriorityQueue
        DataStructuresStudyPack/02_Tree_Structures/Heap_And_PriorityQueue.cpp)
add_executable(Tree_Trie
        DataStructuresStudyPack/02_Tree_Structures/Trie.cpp)
add_executable(Tree_DisjointSetUnion
        DataStructuresStudyPack/02_Tree_Structures/DisjointSetUnion.cpp)

add_executable(Graph_Structures
        DataStructuresStudyPack/03_Graph_Structures/Graph_Structures.cpp)
add_executable(Graph_Representation
        DataStructuresStudyPack/03_Graph_Structures/Graph_Representation.cpp)
add_executable(Graph_DFS
        DataStructuresStudyPack/03_Graph_Structures/DFS.cpp)
add_executable(Graph_BFS
        DataStructuresStudyPack/03_Graph_Structures/BFS.cpp)
add_executable(Graph_TopologicalSort
        DataStructuresStudyPack/03_Graph_Structures/TopologicalSort.cpp)
add_executable(Graph_ShortestPath
        DataStructuresStudyPack/03_Graph_Structures/ShortestPath.cpp)
add_executable(Graph_MinimumSpanningTree
        DataStructuresStudyPack/03_Graph_Structures/MinimumSpanningTree.cpp)
add_executable(Graph_AdvancedAlgorithms
        DataStructuresStudyPack/03_Graph_Structures/Advanced_Graph_Algorithms.cpp)

add_executable(Hash_And_Map
        DataStructuresStudyPack/04_Hash_And_Map/Hash_And_Map.cpp)
add_executable(Hash_HashTable
        DataStructuresStudyPack/04_Hash_And_Map/HashTable.cpp)
add_executable(Hash_HashSet
        DataStructuresStudyPack/04_Hash_And_Map/HashSet.cpp)
add_executable(Hash_HashMap
        DataStructuresStudyPack/04_Hash_And_Map/HashMap.cpp)
add_executable(Hash_BloomFilter
        DataStructuresStudyPack/04_Hash_And_Map/BloomFilter.cpp)

add_executable(Advanced_Data_Structures
        DataStructuresStudyPack/05_Advanced_Data_Structures/Advanced_Data_Structures.cpp)
add_executable(Advanced_FenwickTree
        DataStructuresStudyPack/05_Advanced_Data_Structures/FenwickTree.cpp)
add_executable(Advanced_SegmentTree
        DataStructuresStudyPack/05_Advanced_Data_Structures/SegmentTree.cpp)
add_executable(Advanced_SkipList
        DataStructuresStudyPack/05_Advanced_Data_Structures/SkipList.cpp)
add_executable(Advanced_BTree_And_BPlusTree
        DataStructuresStudyPack/05_Advanced_Data_Structures/BTree_And_BPlusTree.cpp)
add_executable(Advanced_SuffixStructures
        DataStructuresStudyPack/05_Advanced_Data_Structures/SuffixStructures.cpp)

add_executable(Linkage_Examples
        DataStructuresStudyPack/06_Algorithm_DataStructure_Linkage/Linkage_Examples.cpp)

add_executable(Master_Templates
        DataStructuresStudyPack/07_Review_Checklists/Master_Templates.cpp)

