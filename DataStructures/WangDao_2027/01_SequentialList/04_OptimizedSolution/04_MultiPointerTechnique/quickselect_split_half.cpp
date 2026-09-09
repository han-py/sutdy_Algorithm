#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

/**
 * 划分函数：随机选择枢轴，将数组 [left, right] 分为两部分
 * 左边元素 < 枢轴 < 右边元素（元素互异，无相等情况）
 * 返回枢轴最终所在的索引
 */
int partition(int A[], int left, int right) {
    // 随机选择枢轴索引，避免有序数组下的最坏时间复杂度
    int pivotIdx = left + rand() % (right - left + 1);
    swap(A[pivotIdx], A[right]); // 将枢轴移到区间末尾
    int pivot = A[right];

    int i = left - 1; // i 指向最后一个小于枢轴的元素
    for (int j = left; j < right; ++j) {
        if (A[j] < pivot) {
            ++i;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[right]); // 将枢轴放到正确的分界位置
    return i + 1;
}

/**
 * 快速选择算法：将第 target 小的元素放到索引 target 处
 * 此时索引 0 ~ target 的元素为前 target+1 小的元素
 */
void quickSelect(int A[], int left, int right, int target) {
    if (left >= right) return;

    int pos = partition(A, left, right);
    if (pos == target) {
        return; // 已找到目标位置，前 target+1 个元素均为较小的部分
    } else if (pos > target) {
        quickSelect(A, left, pos - 1, target); // 目标在左半区间
    } else {
        quickSelect(A, pos + 1, right, target); // 目标在右半区间
    }
}

/**
 * 例题2-10：将数组较小的一半元素放左侧，较大的一半放右侧
 * 基于快速选择算法，平均时间复杂度 O(n)
 */
void ans(int A[], int n) {
    int half = n / 2; // 较小一半的元素个数
    // 第 half 小的元素对应索引 half-1，前 half 个元素即为较小的一半
    quickSelect(A, 0, n - 1, half - 1);
}

int main() {
#ifdef ACM_LOCAL
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
#endif
    srand(time(0)); // 初始化随机种子，全局只需执行一次

    int A[] = {2, 5, -1, -2};
    int n = 4;
    ans(A, n);

    // 输出结果：前2个为较小的一半，后2个为较大的一半
    for (int i = 0; i < n; ++i) {
        cout << A[i] << " ";
    }
    cout << endl;

    return 0;
}